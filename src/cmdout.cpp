#include <pybind11/pybind11.h>

#include "cmdout.h"

namespace py = pybind11;

bool cmdout::verbose; //defining static members here

cmdout::cmdout(){
    //ctor
    cmdout::verbose = false; // verbosity is set to false by default
}

cmdout::~cmdout(){
    //dtor
}

void cmdout::setVerbose(){
    cmdout::verbose = true;
} 

void cmdout::cmdWrite(bool essential, std::string msg){
    if(essential || cmdout::verbose){
        py::print(msg); //use a python friendly way of output
    }
}