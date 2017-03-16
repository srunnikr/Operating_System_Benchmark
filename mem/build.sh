#!/bin/bash

# remove old building files
rm -rf build/*

# create CMake configuration files inside folder build
cmake -H. -Bbuild

# generate output program in folder build/bin
cmake --build build -- -j3

# create the test file
FILE="test_file"
if [ ! -f $FILE ]; then
	echo ""
	echo "test file does not exist"
	echo "start creating a large test file (may take a few seconds)..."

	# it's better to set the file size as a prime number
	head -c 123456979 < /dev/urandom > test_file
	
	echo "test file is created"
	echo ""
fi
