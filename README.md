# CCCpy
Custom Crowds in C++ for Python. A fork of the CCC software designed to be controlled from Python at the system level using Pybind11.

## System Prerequisites
Designed for UNIX systems and has been tested to work on Ubuntu Linux, Ubuntu via WSL, and MacOS. Only tested using the g++ compiler. 

To compile and use the program, the following must be installed:
- CMake. Set to require version 3.1 or above but easily changed by an experienced user.
- GNU Scientific Library (I used v2.4)
- Visualisation ToolKit (VTK) **v6 or above is required** (I used v6.3)
- Python 2 **exclusively** (This is due to a bug where VTK seems to force Python 2) 

GSL and VTK can be installed on Ubuntu using the following top-level packages:
```
libgsl-dev
libvtk6-dev
```
Output .vtp visualisation files can be read using the ParaView software.

Pybind11 is included as part of the repo. 

TODO: Edit requirements if Python issue is fixed

## Compiling the Python Binary 
The python binary is designed to be compiled via CMake. It is strongly recommended to build in a build directory. A standard build process involves calling the following from the root of the CCCpy directory:
```
mkdir build
cd build
cmake ..
make
```
This will make a compiled Python binary CCCpy(dot)so containing the System class, the main interface for running CCC simulations from Python. 

## Basic Tutorial
Move the compiled binary to the same directory as where you intend to run your Python controlling script. 

To test usage, you can try running the script at /scripts/demonstration.py which demonstrates basic usage of CCCpy - Copy the Python binary to /scripts/ and then from that directory call ``python demonstration.py``. This script creates a subdirectory called 'Demonstration' with CCC files in "experiment format" and runs a simulation demonstrating Active Jamming behaviour (S Henkes, 2011). The .vtp files contained within the 'Demonstration/VTP/' can be opened and displayed in ParaView. 

A tutorial on general usage is provided [here](https://github.com/T-Kozhukhov/CCCpy/wiki). After importing CCCpy in Python you can call ``help(CCCpy)`` to get information on the available function calls and their respective parameters. 
