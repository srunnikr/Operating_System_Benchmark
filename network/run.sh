echo ""
echo "==========================="
echo "Staring Network experiment"
echo "==========================="
echo ""

# Run experiment solely on core 0
taskset -c 0 ./bin/server 5000 &
sleep 2
taskset -c 1 ./bin/client "127.0.0.1" 5000

echo ""
echo "==========================="
echo "Done Network experiment"
echo "==========================="
echo ""
