# Script to demonstrate basic usage of CCCpy. 
# Run this with a copy of the compiled CCCpy binary within the same directory
import sys as system
system.path.insert(1,'/Users/sh18581/Documents/Crowds/CCCpy/build')

import CCCpy # import the CCCpy binary
from utilities import * # import utility python functions

s = CCCpy.System() # make an instance of the System class
#s.setVerbose() #make the system verbose for debug purposes
# Make sure we're not working with debugging input (repeatedly)
#s.setParamDebugMode(0)
# read initial conditions
s.setLoadICData('./corridor.csv')

# now we set up the system's parameters to run an active jamming simulation to demonstrate usage
s.setParamStepSize(0.01)
s=setExperimentDirectory(s, "./Demonstration/", 1,0) #note this utility function recquires that it be called differently
# .def("setParamParticleProperties", &System::setParamParticleProperties, 
#           "Sets information on the individual particles in the system.", "N"_a, "meanR"_a, "sigmaR"_a, 
#            "v_0"_a, "sigmaV"_a, "massRadiusRatio"_a)
print "set initial data" 
#s.setParamParticleProperties(2844, 0.25, 0.3, 0.05, 0, 1)
#print "set particle properties" 
#.def("setParamBoundaryInformation", &System::setParamBoundaryInformation,
#            "Sets information on the boundaries for the system.", "periodic"_a, "L_x"_a, "L_y"_a, "overlapRatio"_a, "collisionMultiplier"_a)
s.setParamBoundaryInformation(True, 30, 9, 0.25,1)
print "set boundary information"

s.setParamHarmonicInterForce(1)
s.setParamActiveForce(0.05, 0.1)
s.setParamGroundFrictionForce(0.1)
s.setParamPersonFrictionForce(0.1)

s.setParamVelocityAlignmentTorque(1)
s.setParamAngularFrictionTorque(0.1)
s.setParamPairDissipationTorque(0.1)
s.setParamRandNoisyTorque(0.1)
s.setParamDirectionCue(1)

#s.setParamDebugMode(6) # use the box debug mode for easier placement of particles

s.prepareSimulation() # prepare the simulation for use
print "finished preparing simulation (including reading data)"

#now the simulation loop
print "starting simulation run"
for i in range(0,1000):
    s.runSimulation(100, 1, 1)
    print "current step: "+str(s.getCurrSimTimeStep())