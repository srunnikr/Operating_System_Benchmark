#!/bin/bash

if [ "$#" -ne 1 ]; then
	echo "Usage ./run <num_iterations>"
	exit
fi

echo ""
echo "==========================="
echo "Making a clean build"
echo "==========================="
echo ""

make clean && make

echo ""
echo "==========================="
echo "Staring experiment"
echo "==========================="
echo ""

# Run experiment solely on core 0
taskset -c 0 ./build/run $1

echo ""
echo "==========================="
echo "Done"
echo "==========================="
echo ""
