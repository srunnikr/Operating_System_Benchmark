if [ "$#" -ne 1 ]; then
	echo "Usage ./run <num_iterations>"
	exit
fi

echo ""
echo "==========================="
echo "Starting CPU experiment"
echo "==========================="
echo ""

# Run experiment solely on core 0
sudo taskset -c 0 nice -n -20 ./build/bin/cpu $1

echo ""
echo "==========================="
echo "Done CPU experiment"
echo "==========================="
echo ""
