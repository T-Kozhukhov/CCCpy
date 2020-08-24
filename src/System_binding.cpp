#include <pybind11/pybind11.h>

#include "System.h"

namespace py = pybind11;

PYBIND11_MODULE(CCCpy, m) {
    //documentation line
    m.doc() = "Custom Crowds in C++ for Python. A fork of the CCC software designed to be controlled from Python at the system level using Pybind11.";
    
    //TODO: add docs for each variable for each member

    py::class_<System>(m, "System") //defining the class
        .def(py::init<>())
        .def("setLoadICData", &System::setLoadICData, "Set the system to load particle IC data on preparation.")
        .def("setVerbose", &System::setVerbose, "Force the system to produce verbose output.")

        .def("setParamStepSize", &System::setParamStepSize, "Sets the timestep size for the system.")
        .def("setParamVTPOutput", &System::setParamVTPOutput, "Sets the VTP output information for the system.")
        .def("setParamParticleProperties", &System::setParamParticleProperties, 
            "Sets information on the individual particles in the system.")
        .def("setParamBoundaryInformation", &System::setParamBoundaryInformation,
            "Sets information on the boundaries for the system.")

        .def("setParamSysStateCSVDir", &System::setParamSysStateCSVDir,
            "Sets the path to place the PhysParam and particle IC state dump csvs.")
        .def("setParamDumpParticles", &System::setParamDumpParticles, 
            "File path to the directory where particle dump data should be stored.")
        .def("setParamDumpParticlesSingleFile", &System::setParamDumpParticlesSingleFile, 
            "Forces single file, single particle dumping. The 0'th particle is targeted.")

        .def("setParamHarmonicInterForce", &System::setParamHarmonicInterForce, 
            "Enable harmonic interactional forces for the system.")
        .def("setParamHertzianInterForce", &System::setParamHertzianInterForce, 
            "Enable hertzian interactional forces for the system.")
        .def("setParamActiveForce", &System::setParamActiveForce, 
            "Enable active (propulsional) forces for the system.")
        .def("setParamGroundFrictionForce", &System::setParamGroundFrictionForce,
            "Enable frictional forces against the ground for the system.")
        .def("setParamPersonFrictionForce", &System::setParamPersonFrictionForce, 
            "Enable frictional forces between particles in the system.")
        .def("setParamRandNoisyForce", &System::setParamRandNoisyForce, 
            "Enable a random noisy Gaussian force on the system.")

        .def("setParamPolarAlignmentTorque", &System::setParamPolarAlignmentTorque, 
            "Enable polar alignment torques for the system.")
        .def("setParamVelocityAlignmentTorque", &System::setParamVelocityAlignmentTorque, 
            "Enable velocity alignment torques for the system.")
        .def("setParamAngularFrictionTorque", &System::setParamAngularFrictionTorque,
            "Enable angular fricional torques for the system.")
        .def("setParamPairDissipationTorque", &System::setParamPairDissipationTorque,
            "Enable pair dissipation torques for the system.")
        .def("setParamRandNoisyTorque", &System::setParamRandNoisyTorque,
            "Enable a random noisy Gaussian torque on the system.")

        .def("setParamDebugMode", &System::setParamDebugMode,
            "Set a debug mode for the system. Used for testing exclusively.")

        .def("writeReadablePhysParam", &System::writeReadablePhysParam, 
            "Output a readable version of the current system parameters.")
        .def("prepareSimulation", &System::prepareSimulation, 
            "Prepares the simulation before running it.")
        .def("runSimulation", &System::runSimulation, 
            "Runs the simulation for T time steps, allowing you to dump either VTP or particle data files as you wish.")
        .def("getCurrSimTimeStep", &System::getCurrSimTimeStep, 
            "Utility function. Returns the current cummulative system time step.")

        .def("dumpVTP", &System::dumpVTP, "Dump VTP files at the current time step.")    
        .def("dumpPartData", &System::dumpPartData, "Dump particle data .csv files at the current time step.");    
}