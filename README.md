# nuMCMC - C++ Markov Chain Monte Carlo Library

**nuMCMC** is a C++ library designed for Markov Chain Monte Carlo (MCMC) simulations, particularly for Bayesian inference and global optimization. It is inspired by the **emcee** Python package and implements the **affine-invariant ensemble sampler** proposed by Goodman & Weare (2010). This library allows efficient exploration of probability distributions, making it useful for parameter estimation, uncertainty quantification, and model fitting.

## Features

- **Ensemble Sampler:** Uses multiple walkers (chains) for efficient parameter space exploration.
- **Parallel Execution:** Supports multi-threading for faster computations.
- **Checkpoints & Resume:** Allows saving and resuming MCMC runs.
- **Simple API:** Define your probability function, initialize walkers, and run MCMC.

---

## Installation

### Prerequisites

- **C++ Compiler**: A modern C++ compiler supporting C++11 or later (GCC, Clang, MSVC).
- **CMake**: Required for building the library.
- **Optional:** Ninja for faster builds on Windows.

### Build Instructions

Clone the repository and create a build directory:

```bash
git clone https://github.com/MarianoChaves/MCMC.git
cd MCMC
mkdir build && cd build

Run CMake to generate build files:

cmake ../ -DCMAKE_CXX_STANDARD=11

Compile the library:

make -j4    # or use 'ninja' if configured

For Windows users using MSYS2:

cmake ../ -G "Ninja" -DCMAKE_CXX_STANDARD=11
ninja


---

Quick Start Guide

1. Define a Log-Probability Function

To use nuMCMC, you need to define a function that computes the log-probability of the model parameters:

#include <vector>
#include <cmath>

double logProbability(const std::vector<double>& params) {
    double x = params[0];
    return -0.5 * x * x;  // Log-Normal(0,1)
}

2. Configure and Run MCMC

#include "MCMC.h"
#include <iostream>
#include <random>

int main() {
    int numParams = 1;     // One-dimensional parameter space
    int numWalkers = 10;   // Number of walkers
    int numSteps = 5000;   // Total iterations

    // Initialize walkers in the range [-5,5]
    std::vector<std::vector<double>> initPos(numWalkers, std::vector<double>(numParams));
    std::mt19937 gen(1234);
    std::uniform_real_distribution<double> dist(-5.0, 5.0);
    for (int i = 0; i < numWalkers; ++i) initPos[i][0] = dist(gen);

    // Set up and run MCMC
    MCMC sampler(numParams, numWalkers);
    sampler.setLogProbabilityFunction(logProbability);
    sampler.initializeWalkers(initPos);
    sampler.run(numSteps);

    // Retrieve samples
    auto samples = sampler.getSamples();
    std::cout << "Total samples generated: " << samples.size() << std::endl;
}


---

Example Applications

Example 1: Bayesian Inference of a Parameter

Let's assume we have observed data from a Normal(μ, σ=1) distribution and want to estimate μ using Bayesian inference.

Log-Posterior Function

#include <vector>
#include <cmath>

// Example data (simulated observations)
std::vector<double> data = {1.8, 2.4, 1.9, 2.2, 2.0, 2.3};

// Log-Posterior (Log-Likelihood + Log-Prior)
double logPosteriorMu(const std::vector<double>& params) {
    double mu = params[0];
    double logPrior = -0.5 * (mu / 5.0) * (mu / 5.0);  // Prior: Normal(0,5)
    double logLike = 0.0;
    for (double x : data) logLike += -0.5 * (x - mu) * (x - mu);
    return logPrior + logLike;
}

Running MCMC for Inference

int main() {
    int numParams = 1;
    int numWalkers = 8;
    int numSteps = 5000;

    // Initialize walkers in range [-10,10]
    std::vector<std::vector<double>> initPos(numWalkers, std::vector<double>(numParams));
    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(-10.0, 10.0);
    for (int i = 0; i < numWalkers; ++i) initPos[i][0] = dist(gen);

    MCMC sampler(numParams, numWalkers);
    sampler.setLogProbabilityFunction(logPosteriorMu);
    sampler.initializeWalkers(initPos);
    sampler.run(numSteps);

    auto chain = sampler.getSamples();
    double sum = 0.0;
    for (double mu : chain) sum += mu;
    double meanMu = sum / chain.size();
    std::cout << "Estimated mu = " << meanMu << std::endl;
}


---

Example 2: Global Optimization Using MCMC

MCMC can also be used to explore complex functions and locate global maxima. Consider:

f(x) = - (x^2 - 1)^2

which has two peaks at x = ±1. By treating this function as a probability distribution (after scaling), we can find these peaks using MCMC.

Log-Probability Function for Optimization

double logProbObjective(const std::vector<double>& params) {
    double x = params[0];
    return -std::pow(x * x - 1.0, 2);
}

Running MCMC to Find Peaks

int main() {
    int numParams = 1;
    int numWalkers = 6;
    int numSteps = 10000;

    // Initialize walkers randomly in [-5,5]
    std::vector<std::vector<double>> initPos(numWalkers, std::vector<double>(numParams));
    std::mt19937 gen(7);
    std::uniform_real_distribution<double> dist(-5.0, 5.0);
    for (int i = 0; i < numWalkers; ++i) initPos[i][0] = dist(gen);

    MCMC sampler(numParams, numWalkers);
    sampler.setLogProbabilityFunction(logProbObjective);
    sampler.initializeWalkers(initPos);
    sampler.run(numSteps);

    auto samples = sampler.getSamples();
    int countLeft = 0, countRight = 0;
    for (double x : samples) {
        if (x < 0) countLeft++;
        else countRight++;
    }
    std::cout << "Samples near x<0: " << countLeft << ", near x>0: " << countRight << std::endl;
}

Expected Output: Approximately equal samples around x=-1 and x=1, confirming that MCMC found the two peaks.


---

Visualization of MCMC Results

To analyze MCMC performance, consider:

Trace Plots: Show parameter evolution across iterations.

Histograms: Estimate the posterior density of parameters.

Scatter Plots: Identify correlations between parameters.

Corner Plots: Summarize multidimensional posteriors.


Using Python (Matplotlib), you can visualize the results:

import matplotlib.pyplot as plt
import numpy as np

samples = np.loadtxt("samples.csv")  # Assume samples saved in a CSV
plt.hist(samples, bins=50, density=True)
plt.title("Posterior Distribution of Parameter")
plt.xlabel("Parameter Value")
plt.ylabel("Density")
plt.show()


---

Advanced Use Cases

Scientific Computing: Bayesian inference in physics, astrophysics, and chemistry.

Machine Learning: Estimation of Bayesian models and uncertainty quantification.

Financial Modeling: Parameter estimation in risk assessment.

Parallel Computing: Run chains in parallel using run_parallel().



---

License

nuMCMC is open-source and licensed under the MIT License.


---

This documentation provides a complete guide to using nuMCMC for probabilistic modeling and optimization. Happy sampling!

---

