if [ "$#" -ne 1 ]; then
	echo "Usage ./run <num_iterations>"
	exit
fi

echo ""
echo "==========================="
echo "Staring CPU experiment"
echo "==========================="
echo ""

# Run experiment solely on core 0
sudo taskset -c 0 nice -n -20 ./build/run $1

echo ""
echo "==========================="
echo "Done CPU experiment"
echo "==========================="
echo ""
