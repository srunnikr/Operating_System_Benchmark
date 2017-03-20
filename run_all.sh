#!/bin/bash

if [ "$#" -ne 1 ]; then
	echo "Usage ./run <num_iterations>"
	exit
fi

echo ""
echo "========================="
echo "Running experiments"
echo "========================="
echo ""

echo ""
echo "-------------------------"
echo "CPU"
echo "-------------------------"
echo ""
cd cpu
./run.sh $1
cd ..

echo ""
echo "-------------------------"
echo "MEMORY"
echo "-------------------------"
echo ""
cd mem
./run.sh
cd ..

echo ""
echo "-------------------------"
echo "NETWORK"
echo "-------------------------"
echo ""
cd network
./run.sh
cd ..

echo ""
echo "-------------------------"
echo "FILE SYSTEM"
echo "-------------------------"
echo ""
cd fs
./run.sh
cd ..

echo ""
echo "========================="
echo "Done!"
echo "========================="
echo ""
