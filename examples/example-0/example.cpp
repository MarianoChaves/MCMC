#include<vector>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include <time.h> 

#include "../../nu.h"

double loglike(std::vector<double> params){
    double logL = 0;
    double mean[3] = {50,1,20};
    double dev[3] = {1,1,20};
    for(int i = 0; i<3; i++){
        logL += (params[i]-mean[i])*(params[i]-mean[i])/(dev[i]*dev[i]);
    };
    logL += -0.5*(params[0]-mean[0])*(params[1]-mean[1])/(dev[0]*dev[1]);
    logL += -0.5*(params[2]-mean[2])*(params[1]-mean[1])/(dev[2]*dev[1]);

    return -0.5*logL;
};

int main(){

    

    /*NU_MCMC RUNNING TESTS*/
    srand(42);

    int nwalkers = 250;
    int ndim = 3;


    std::vector< std::vector<double> > init_pos;

    for(int k = 0; k < nwalkers; k++){
        double p1 = double(rand()% 200+500)/10;
        double p2 = double(rand()% 100+1)/10;
        double p3 = double(rand()% 200+1)/10;
        std::vector<double> pos{p1,p2,p3};
        init_pos.push_back(pos);

    }
    char file_name[256] = "test_state.csv"; 
    
    nu::Mcmc my_sample(nwalkers, ndim, init_pos);

    my_sample.run(loglike, 0);

    /*If you want to save a state */
    
    my_sample.save_state(file_name);

}