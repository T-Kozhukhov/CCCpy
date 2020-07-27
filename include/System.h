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

        /// TODO: function to set up experiment format directories?
        /// TODO: function to set up loading particle data
        /// TODO: function to set verbosity
        /// TODO: test how the cmdout class works in pybind

        /// TODO: grouped functions for handling the physParam, ensure they only work when the simulation is not prepped
        /// TODO: function to dump current parameters in a long list - Maybe try extracting those from the readable output?
        /// TODO: function to set up dumping of single file (can only work when sim not prepared)

        void prepareSimulation(); // function which prepares the simulation to be run
        /// TODO: make a runSimulation function which runs N timesteps and then dumps visualiser data, 
                /// should keep track of which total timestep it's on so it can dump partData correctly. Only runs 
                /// after sim is prepped and will ensure simBegun=true
        void runSimulation(); // begins the simulation according to sysParam

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
