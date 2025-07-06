# Quick Start

This section outlines a minimal example of running nuMCMC.

```cpp
#include "MCMC.h"

// Define your log probability
double logProbability(const std::vector<double>& params) {
    double x = params[0];
    return -0.5 * x * x; // standard normal
}

int main() {
    numcmc::MCMC sampler(1, 10); // dimension=1, 10 walkers
    sampler.setLogProbabilityFunction(logProbability);
    sampler.run(5000);
    auto samples = sampler.getSamples();
}
```
