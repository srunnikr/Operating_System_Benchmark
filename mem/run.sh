#!/bin/bash

echo ""
echo "==========================="
echo "Starting Memory experiment"
echo "==========================="
echo ""

# root permission is required to execute flush memory cache command 
#sudo ./build/bin/mem
sudo taskset -c 0 nice -n -20 ./build/bin/mem

echo ""
echo "==========================="
echo "Done Memory experiment"
echo "==========================="
echo ""
