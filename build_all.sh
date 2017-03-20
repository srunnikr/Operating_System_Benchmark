#!/bin/bash

echo "========================="
echo "Building source files"
echo "========================="

echo ""
echo "-------------------------"
echo "CPU"
echo "-------------------------"
cd cpu
./build.sh
cd ../

echo ""
echo "-------------------------"
echo "MEMORY"
echo "-------------------------"
echo ""
cd mem
./build.sh
cd ../
echo ""

echo ""
echo "-------------------------"
echo "NETWORK"
echo "-------------------------"
echo ""
cd network
./build.sh
cd ../
echo ""

echo ""
echo "-------------------------"
echo "FILE SYSTEM"
echo "-------------------------"
echo ""
cd fs
./build.sh
cd ../
echo ""
