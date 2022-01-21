#ifndef MCMC_H
#define MCMC_H

#include <math.h>
#include <time.h>

#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "numcmc/ensemble.h"
#include "numcmc/walker.h"

namespace nu {
class Mcmc {
   private:
    Ensemble sample;
    int nwalkers;
    int ndim;

    // Cumulative Inverse of g(z)
    double F(double z) { return 0.5 * (z * z + 2 * z + 1); };
    bool constrained = true;

    std::vector<std::vector<double>> load_state(char *file_name);

   public:
    int run(double (*func)(std::vector<double> &), int steps);
    int run_parallel(double (*func)(std::vector<double> &), int steps,
                     int threads);
    int run_notlog(double (*func)(std::vector<double> &), int steps);
    int reset();
    int save_state(char *file_name);

    std::vector<std::vector<double>> get_chain();
    std::vector<std::vector<double>> get_chain_walkers();
    int save_chain(char *file_name, char *header);
    int save_chain_walker(char *file_name, char *header);

    Mcmc(int K, int N, std::vector<std::vector<double>> init_sample);
    Mcmc(int K, int N, char *file_name);
    ~Mcmc(){};
};

}  // namespace nu

#endif