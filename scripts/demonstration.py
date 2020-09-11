# Script to demonstrate basic usage of CCCpy. 
# Run this with a copy of the compiled CCCpy binary within the same directory

import CCCpy # import the CCCpy binary
from utilities import * # import utility python functions

s = CCCpy.System() # make an instance of the System class
#s.setVerbose() #make the system verbose for debug purposes

# now we set up the system's parameters to run an active jamming simulation to demonstrate usage
s.setParamStepSize(0.01)
s=setExperimentDirectory(s, "./Demonstration/", 1, 0) #note this utility function recquires that it be called differently
s.setParamParticleProperties(500, 1, 0.03, 0.05, 0, 1)
s.setParamBoundaryInformation(False, 40, 40, 0.25, 1)

s.setParamHarmonicInterForce(1)
s.setParamActiveForce(0.05, 0.1)
s.setParamGroundFrictionForce(0.1)
s.setParamPersonFrictionForce(0.1)

s.setParamVelocityAlignmentTorque(1)
s.setParamAngularFrictionTorque(0.1)
s.setParamPairDissipationTorque(0.1)
s.setParamRandNoisyTorque(0.1)

s.setParamDebugMode(6) # use the box debug mode for easier placement of particles

s.prepareSimulation() # prepare the simulation for use

#now the simulation loop
for i in range(1,1000):
    s.runSimulation(250, 1, 1)
    print "current step: "+str(s.getCurrSimTimeStep())