# nuMCMC - C++ Markov Chain Monte Carlo Library

**nuMCMC** is a lightweight C++ library for **Markov Chain Monte Carlo (MCMC) simulations**, designed for Bayesian inference and optimization. Inspired by the **emcee** Python package, it implements an **affine-invariant ensemble sampler**, making it efficient for high-dimensional parameter estimation.

## Features

✅ **Easy-to-use API** – Define a log-probability function, set up walkers, and run MCMC  
✅ **Parallel Execution** – Run walkers in multiple threads for speed  
✅ **Checkpointing** – Save and resume MCMC runs  
✅ **Minimal Dependencies** – Uses standard C++ (no extra libraries required)  

---

## 📥 Installation

### Requirements:
- A C++ compiler supporting **C++11 or later** (GCC, Clang, MSVC)
- **CMake** (for building the project)

### Build Instructions:

1. Clone the repository:
   ```bash
   git clone https://github.com/MarianoChaves/MCMC.git
   cd MCMC
   ```

2. Create a build directory and compile:
   ```bash
   mkdir build && cd build
   cmake ..
   make -j4   # Or use 'ninja' if installed
   ```

3. For Windows (MSYS2), use:
   ```bash
   cmake .. -G "Ninja"
   ninja
   ```

---

## 🚀 Quick Start

### 1️⃣ Define a Log-Probability Function

The core of MCMC is defining a function that computes the log-probability:

```cpp
double logProbability(const std::vector<double>& params) {
    double x = params[0];
    return -0.5 * x * x;  // Log of a standard Normal(0,1) distribution
}
```

### 2️⃣ Run MCMC with nuMCMC

```cpp
#include "MCMC.h"

MCMC sampler(1, 10);  // 1 parameter, 10 walkers
sampler.setLogProbabilityFunction(logProbability);
sampler.run(5000);  // Run for 5000 iterations

auto samples = sampler.getSamples();  // Retrieve generated samples
```

🎯 That's it! You've just performed MCMC sampling in C++.

---

## 📚 Examples

For full working examples, check the examples directory in the repository.
Examples include:

- Basic MCMC sampling
- Bayesian inference of a parameter
- Global optimization using MCMC

To compile and run an example:

```bash
cd examples
g++ example1.cpp -o example1 -std=c++11
./example1
```

---

## 📊 Visualizing MCMC Results

You can analyze the MCMC results by plotting the generated samples. If you save them to a file (samples.csv), you can visualize them with Python:

```python
import matplotlib.pyplot as plt
import numpy as np

samples = np.loadtxt("samples.csv")
plt.hist(samples, bins=50, density=True)
plt.title("Posterior Distribution")
plt.show()
```

---

## ⚡ Advanced Usage

- Use run_parallel() for multithreaded execution
- Define multi-parameter models by setting dim > 1
- Save and resume MCMC chains for long-running simulations

For more details, see the full documentation.

---

## 📜 License

This project is licensed under the MIT License.

🚀 Start exploring your data with nuMCMC today!