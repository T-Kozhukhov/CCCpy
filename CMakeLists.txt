cmake_minimum_required(VERSION 3.1)
project(CCCpy) #project name
set(CMAKE_BUILD_TYPE Release) #force release build

#normal stuff
include_directories(include) #add headers
file(GLOB SOURCES "src/*.cpp") #add source files

#GSL
find_package(GSL REQUIRED) #add GSL libraries

#VTK
find_package(VTK REQUIRED) #add VTK libs
include(${VTK_USE_FILE}) # include vtk libs
set(VTK_PYTHON_VERSION=3) # give VTK the flag that we're using python3
#TODO: Edit the above if a fix is not found to set the most recent version of python 2 (2.7?)

#pybind stuff
set(PYBIND11_PYTHON_VERSION 3.6) #tell pybind we want to use python 3.6
#TODO: Edit the above if a fix is not found to set the most recent version of python 2 (2.7?)
add_subdirectory(pybind11) #adds the subdirectory of pybind11 (containing the library)
pybind11_add_module(CCCpy ${SOURCES}) #makes a python module by using all specified source files 
    # the binding file is the only one that really matters, but this is how you tell it about which source files to use

#link libraries
target_link_libraries(CCCpy PRIVATE GSL::gsl GSL::gslcblas) #link GSL libs
target_link_libraries(CCCpy PRIVATE ${VTK_LIBRARIES}) #link VTK libs

#force output binary to have name CCCpy.so
set_target_properties(CCCpy PROPERTIES OUTPUT_NAME CCCpy)
set_target_properties(CCCpy PROPERTIES SUFFIX .so)

#TODO: init fix issue is due to VTK forcing python 2, see if you can set a flag to force it to use python 3