# Utility functions for use with CCCpy.

import CCCpy
import math
import os

# TODO: Consider making a utility to help generate IC data for particles - Similar to the helper functions in the bManager class.

# TODO: Consider making a utility class to hold information for particles, and also loading them from ParticleData csvs and dumping initParticleDatas after construction

def smartMkDir(dir):
    # A smart os.mkdir which only makes a directory if it doesn't exist
    if not os.path.exists(dir):
        os.mkdir(dir)

def setExperimentDirectory(s, pathToDir, dumpingType, singleDumpID):
    # Returns a System with experiment directories created and set accordingly
    # particle dumping depends on the last argument: 0-No part dump, 1-multi file part dump, 2-single file part dump

    partDataDir = pathToDir+"ParticleData/"
    VTPDataDir = pathToDir+"VTP/" # construct strings for paths to vtp and particle data

    #make directories
    smartMkDir(pathToDir)
    smartMkDir(partDataDir)
    smartMkDir(VTPDataDir)

    #now tell the system about these new directories as appropriate
    s.setParamVTPOutput(VTPDataDir, "VisualiserData")
    s.setParamSysStateCSVDir(pathToDir)
    if dumpingType == 2: #dump particle data depending on relevent argument
        s.setParamDumpParticlesSingleFile(partDataDir, singleDumpID)
    else:
        s.setParamDumpParticles(dumpingType, partDataDir)
    return s #at the end return the system

# TODO: test function
def setNoFromDensity(s, density, L_x, L_y, meanR, sigmaR, v_0, sigmaV, massRadiusRatio, periodic, overlapRatio):
    # Set the number of particles from the density of the system and the size. 
    # Effectively a wrapper for setParamParticleProperties() and setParamBoundaryInformation()
    area = L_x * L_y
    N =  round(density*area/(math.pi*meanR**2)) # compute ideal number of particles

    # set the particle properties and boundary information and return
    s.SetParamParticleProperties(N, meanR, sigmaR, v_0, sigmaV, massRadiusRatio)
    s.setParamBoundaryInformation(periodic, L_x, L_y, overlapRatio)
    return s

# TODO: test function
def setBoxFromDensity(s, density, N, meanR, sigmaR, v_0, sigmaV, massRadiusRatio, periodic, overlapRatio):
    # Set the size of the boundary box fropm the density of the system and the number of intended particles.
    # Effectively a wrapper for setParamParticleProperties() and setParamBoundaryInformation()
    L = math.sqrt(N*math.pi*meanR**2/density) # compute the length recquired

    #set the particle properties and boundary information and return
    s.SetParamParticleProperties(N, meanR, sigmaR, v_0, sigmaV, massRadiusRatio)
    s.setParamBoundaryInformation(periodic, L, L, overlapRatio)
    return s