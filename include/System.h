#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>

#include "person.h"
#include "neighbourList.h"
#include "boundaryManager.h"
#include "force.h"
#include "planarTorque.h"
#include "output.h"

class System
{
    public: //functions in here are those that will be bound in the end
        System();
        System(physParam param);
        virtual ~System();

        // Functions that bind like CCC program arguments ////////////////////////////////////////////
        /// TODO: function to set up experiment format directories?
        /// TODO: function to set up loading particle data
        void setVerbose(); //set whether the system is verbose or not
        /// TODO: test how the cmdout class works in pybind

        // Functions which bind physParam setting ////////////////////////////////////////////////////
        /// TODO: grouped functions for handling the physParam, ensure they only work when the simulation is not prepped
        void setParamStepSize(double stepSize); //sets step size for the sim
        void setParamVTPOutput(std::string outPath, std::string outFileName); //sets vtp output information for the sim
        void setParamParticleProperties(int N, double meanR, double sigmaR, double v_0, double sigmaV, double massRadiusRatio); //sets information on individual particles for the sim
        void setParamBoundaryInformation(bool periodic, double L_x, double L_y, double overlapRatio); //sets information on the boundary for the sim
       
        void setParamSysStateCSVDir(std::string pathToSysStateDir); //sets the path to place the phyparam and init particle state csvs
        void setParamDumpParticles(int dumpEveryNSteps, std::string pathToParticleData); // file path to the dir where particle data should be stored
        void setParamDumpParticlesSingleFile(std::string pathToParticleData); //dumps data on particle #0 to the specified path
        
        // Force sets
        void setParamHarmonicInterForce(double kHarmonic);
        void setParamHertzianInterForce(double kHertzian);
        void setParamActiveForce(double v_0, double zetaActive);
        void setParamGroundFrictionForce(double zetaGround);
        void setParamPersonFrictionForce(double zetaPerson);
        void setParamRandNoisyForce(double sigmaForceX, douvble sigmaForceY);

        // Torque sets
        void setParamPolarAlignmentTorque(double zetaPolar);
        void setParamVelocityAlignmentTorque(double zetaVelocity);
        void setParamAngularFrictionTorque(double xiAngular);
        void setParamPairDissipationTorque(double xiPair);
        void setParamRandNoisyTorque(double sigmaTorque);
        
        void setParamDebugMode(int mode); // used for setting up simulations into specific debug states
        
        // Main functions for operation //////////////////////////////////////////////////////////////
        void writeReadablePhysParam(); //writes out the current parameters in readable form
        void prepareSimulation(); // function which prepares the simulation to be run
        /// TODO: make a runSimulation function which runs N timesteps and then dumps visualiser data, 
                /// should keep track of which total timestep it's on so it can dump partData correctly. Only runs 
                /// after sim is prepped and will ensure simBegun=true
        void runSimulation(); // begins the simulation according to sysParam
        int getCurrSimTimeStep(); // returns the current time step since the simulation began

        /// TODO: make a minimal version of pybind11 that can be included instead of my 115mb one!!!!

    private:
        //system parameters
        physParam sysParam; // all global parameters particular system

        //Jenny
        RNG randGen; // the random number generator for the system

        //set up subroutines
        void initParticles(); // initialises the particles for the simulation

        std::vector<person> personList; // main list of particles, ie the pList

        //dynamics functions
        void step(int t); // performs a single time step
        void calculateForcesTorques(int i); //calculates all the forces for the person at index i in the list
        void generateDebugParticles(); //generate hardcoded particles in order to debug

        //auxiliary functions
        void mergePList(std::vector<person> newList); //merges newList into the main personList
        void mergePList(std::vector<person> *parentList, std::vector<person> newList); //merges newList into parentList
        bool checkParamEditable(); //checks to see if the sysParam is editable. If not, output why.

        //helper objects/ managers
        boundaryManager bManager;
        force fManager;
        planarTorque tManager;
        output vtpDumper;

        //assorted variables
        bool simulationBegun; //whether the simulation has begun or not, used for error catching
        bool simulationReady;
};

#endif // SYSTEM_H
