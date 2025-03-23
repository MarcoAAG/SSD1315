#! /bin/bash

cd ..
if [ ! -d "documentation/" ] 
then
    mkdir documentation
fi

~/Tools/doxygen/1.12.0/doxygen config-doxygen.conf 2> documentation/doxygen.log