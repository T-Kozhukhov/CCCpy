# CCCpy
Custom Crowds in C++ for Python. A fork of the CCC software designed to be controlled from Python at the system level using Pybind11.

## System Prerequisites
Designed for UNIX systems and has been tested to work on Ubuntu Linux, Ubuntu via WSL, and MacOS. Only tested using the g++ compiler. 

To compile and use the program, the following must be installed:
- CMake. Set to require version 3.1 or above but easily changed by an experienced user.
- GNU Scientific Library (I used v2.4)
- Visualisation ToolKit (VTK) **v6 or above is required** (I used v6.3)
- Python 2 (This is due to a bug where VTK seems to force Python 2) 

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

## Usage and Tutorial
TODO: Write guide on general usage, and a rough top level tutorial on how to get a basic simulation going. 

TODO: Perhaps provide full documentation on what bindings are available in a seperate file/ wiki? Make sure build in Python docs work!!!