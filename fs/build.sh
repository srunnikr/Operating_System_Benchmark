#!/bin/bash

# remove old building files
rm -rf build/*

# create CMake configuration files inside folder build
cmake -H. -Bbuild

# generate output program in folder build/bin
cmake --build build -- -j3

# generate the test files
echo ""
echo "start creating test files..."
python generate_files.py
echo "creation finished."
echo ""
