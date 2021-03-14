#include<vector>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include <time.h> 

#include "src/walker.h"
#include "src/ensemble.h"
#include "src/emcee.h"

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

    

    /*EMCEE RUNNING TESTS*/
    if(true){
        srand(42);

        int nwalkers = 250;
        int ndim = 3;
        int bournout = 50;
        int nsteps = 50;


        std::vector< std::vector<double> > init_pos;

        for(int k = 0; k < nwalkers; k++){
            double p1 = double(rand()% 200+500)/10;
            double p2 = double(rand()% 100+1)/10;
            double p3 = double(rand()% 200+1)/10;
            std::vector<double> pos{p1,p2,p3};
            init_pos.push_back(pos);

        }
        char file_name[256] = "test_state.csv"; 
        
        //nu::Emcee my_sample(nwalkers, ndim, init_pos);
        nu::Emcee my_sample(nwalkers, ndim, file_name);

        my_sample.run_mcmc(loglike, bournout);
        std::cout<<"\n\n****Burnout done!****\n\n";

        /*If you want to save a state */
        
        my_sample.save_state(file_name);

        /*If you don't load an state */
        //my_sample.reset();
        //my_sample.run_mcmc(loglike, nsteps);
        //std::cout<<"\n\n****EMCEE done!****\n\n";

        /*If you load an state*/
        //my_sample.load_state(file_name);
        //my_sample.run_mcmc(loglike, nsteps);
        //std::cout<<"\n\n****EMCEE done!****\n\n";


        char file_sample_name[256] = "samples.csv";
        char header[256] = "x,y,z,walker\n";
        my_sample.save_chain_walker(file_sample_name,header);        

    };

    /*EMCEE INPUT AND CHAIND TESTS*/
    if(false){
        // Vector dimensions
        int nwalkers = 4;
        int ndim = 3;
        // Creating veactors of initial position for each walker
        std::vector<double> pos1{1.1,1.2,1.3};
        std::vector<double> pos2{2.1,2.2,2.3};
        std::vector<double> pos3{3.1,3.2,3.3};
        std::vector<double> pos4{4.1,4.2,4.4};
        // Creatig vectors of vectors of initial positions
        std::vector< std::vector<double> > init_pos{pos1,pos2,pos3,pos4};

        // Initialize emcee
        nu::Emcee my_first_sample(nwalkers, ndim, init_pos);

        // Get the final chain, in that case only the initial beacuse we have not runned
        std::vector< std::vector<double> > sampling_points;
        sampling_points = my_first_sample.get_chain();


        /*Writing samples*/
        std::ofstream sampling_file;

        sampling_file.open ("samples.csv");
        sampling_file << "x,y,z\n";
        
        for(int i = 0; i< nwalkers ; i++){
            for(int j = 0; j < ndim ; j++){
                sampling_file << sampling_points[i][j];
                if(j!=ndim-1) sampling_file <<",";
            };
            if(i!=nwalkers-1) sampling_file<<std::endl;
        };
        
        sampling_file.close();

    };

    /*ENSEMBLE TEST */
    if(false){
        //dimension
        int ndim = 3;
        int nwalkers = 2;

        //creating initial positions for each walker
        std::vector< double> init_pos1{1.1,1.2,1.3};
        std::vector< double> init_pos2{2.1,2.2,2.3};
        std::vector< double> init_pos3{3.1,3.2,3.3};

        //initiaizing walkers in the initial positions
        nu::Walker walker_1(ndim, init_pos1);
        nu::Walker walker_2(ndim, init_pos2);
        nu::Walker walker_3(ndim, init_pos3);

        //create a vector of walkers, necessary to initialize ensemble
        std::vector< nu::Walker> my_walkers{walker_1, walker_2};

        //initialize ensemble
        nu::Ensemble my_first_ensemble(nwalkers, ndim, my_walkers);

        //include a new walker
        my_first_ensemble.includeWalker(walker_3);

        //take the walker 1, it removes the walker from the emsemble
        nu::Walker test1 = my_first_ensemble.getWalker(1);
        //take a copy of the actual walkers 1 and 2
        nu::Walker test2 = my_first_ensemble.getWalkerCopy(1);
        nu::Walker test3 = my_first_ensemble.getWalkerCopy(2);

        //print the walkers positions
        std::cout<<"First Walker: " << test1.getPos()[0]<<", "<< test1.getPos()[1]<<", " << test1.getPos()[2] <<"\n";
        std::cout<<"First Walker when the First was dropped: " << test2.getPos()[0]<<", "<< test2.getPos()[1]<<", " << test2.getPos()[2] <<"\n";
        std::cout<<"Second Walker when the First was dropped: " << test3.getPos()[0]<<", "<< test3.getPos()[1]<<", " << test3.getPos()[2] <<"\n";

        //substitute a walker
        my_first_ensemble.substituteWalker(1,walker_1);
        nu::Walker test4 = my_first_ensemble.getWalkerCopy(1);

        std::cout<<"Substituted the actual First Walker by the older first walker: " << test4.getPos()[0]<<", "<< test4.getPos()[1]<<", " << test4.getPos()[2] <<"\n";

    }

    /* WALKER TEST */
    if(false){
        //dimension of the walker space
        int ndim = 3;

        srand(42);

        //nu::Walker my_first_walker(ndim); /* In case you prefer to begin with a void walker  */

        //a vector initial position with ndim dimensions, necessary 
        //when initialze the walker in a position
        std::vector< double> first_position(ndim, rand() %10 + 1);
        nu::Walker my_first_walker(ndim, first_position);

        std::vector< double> second_position{1.1,2.2,3.3};
        std::vector< double> third_position{1.01,2.02,3.03};

        //make the walker walk
        //my_first_walker.setPos(first_position); /* In case you prefer to begin with a void walker  */
        my_first_walker.setPos(second_position);
        my_first_walker.setPos(third_position);

        std::cout<<"Steps:" << my_first_walker.getSteps()<<"\n";

        std::cout<<"Actual Position:" << my_first_walker.getPos()[0]<<", "<< my_first_walker.getPos()[1]<<", " << my_first_walker.getPos()[2] <<"\n";

        std::cout<<"First Position:" << my_first_walker.getPos(1)[0]<<", " << my_first_walker.getPos(1)[1]<<", " << my_first_walker.getPos(1)[2] <<"\n";

        std::cout<<"Second Position:" << my_first_walker.getPos(2)[0]<<", " << my_first_walker.getPos(2)[1]<<", " << my_first_walker.getPos(2)[2] <<"\n";
    };

}