#ifndef EMCEE_H
#define EMCEE_H

#include<math.h>
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include<limits>
#include "walker.h"
#include "ensemble.h"


namespace nu
{
    class Emcee{
        private:
            Ensemble sample;
            int nwalkers;
            int ndim;

            //Cumulative Inverse of g(z)
            double F(double z){
                return 0.5*(z*z+2*z+1);
            };

            std::vector< std::vector<double> > load_state(char *file_name);

        public:
            int run_mcmc(double (*func)(std::vector<double>), int steps);
            int reset();
            int save_state(char *file_name);
            

            std::vector< std::vector<double> > get_chain();
            std::vector<std::vector<double> > get_chain_walkers();
            int save_chain(char *file_name, char* header);
            int save_chain_walker(char *file_name, char* header);


            Emcee(int K, int N, std::vector<std::vector<double>> init_sample);
            Emcee(int K, int N, char *file_name);
            ~Emcee(){};

    };

}


#endif