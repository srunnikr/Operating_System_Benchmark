if [ "$#" -ne 1 ]; then
	echo "Usage ./run <num_iterations>"
	exit
fi

echo "========================="
echo "Building source files"
echo "========================="

echo ""
echo "-------------------------"
echo "CPU"
echo "-------------------------"
cd cpu
make clean && make
cd ../

echo ""
echo "-------------------------"
echo "NETWORK"
echo "-------------------------"
echo ""
cd network
cmake .
make clean && make
cd ../
echo ""

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
echo "NETWORK"
echo "-------------------------"
echo ""
cd network
./run.sh
cd ..


echo ""
echo "========================="
echo " CLEANING UP"
echo "========================="
echo ""
cd cpu
make clean
cd ../network
make clean

echo ""
echo "========================="
echo "Done!"
echo "========================="
echo ""