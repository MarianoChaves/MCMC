#include <stdlib.h>
#include <time.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "numcmc/nu.h"


double loglike(std::vector<double> &params) {
    double logL = 0;
    double mean[3] = {50, 1, 20};
    double dev[3] = {1, 1, 20};
    for (int i = 0; i < 3; i++) {
        logL +=
            (params[i] - mean[i]) * (params[i] - mean[i]) / (dev[i] * dev[i]);
    };
    logL += -0.5 * (params[0] - mean[0]) * (params[1] - mean[1]) /
            (dev[0] * dev[1]);
    logL += -0.5 * (params[2] - mean[2]) * (params[1] - mean[1]) /
            (dev[2] * dev[1]);

    return -0.5 * logL;
};

int main() {
    /*NU_MCMC RUNNING TESTS*/
    srand(42);

    int nwalkers = 250;
    int ndim = 3;
    int bournout = 50;
    int nsteps = 100;

    std::vector<std::vector<double> > init_pos;
    for (int k = 0; k < nwalkers; k++) {
        double p1 = double(rand() % 200 + 500) / 10;
        double p2 = double(rand() % 100 + 1) / 10;
        double p3 = double(rand() % 200 + 1) / 10;
        std::vector<double> pos{p1, p2, p3};
        init_pos.push_back(pos);
    }

    clock_t tStart;

    nu::Mcmc my_sample(nwalkers, ndim, init_pos);
    my_sample.run(loglike, bournout);
    std::cout << "\n\n****Burnout done!****\n\n";
    my_sample.reset();

    tStart = clock();
    int threads = 3;
    my_sample.run_parallel(loglike, nsteps, threads);
    tStart = clock() - tStart;
    std::cout << "\n\nParallel time of execution: "
              << (double)(tStart) / CLOCKS_PER_SEC << " s" << std::endl;

    tStart = clock();
    my_sample.run(loglike, nsteps);
    tStart = clock() - tStart;
    std::cout << "\n\nSerial time of execution: "
              << (double)(tStart) / CLOCKS_PER_SEC << " s" << std::endl;

    char file_sample_name[256] = "samples.csv";
    char header[256] = "x,y,z,walker\n";
    my_sample.save_chain_walker(file_sample_name, header);
}