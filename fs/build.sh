#!/bin/bash

# remove old building files
rm -rf build/*

# create CMake configuration files inside folder build
cmake -H. -Bbuild

# generate output program in folder build/bin
cmake --build build -- -j3
