echo ""
echo "==========================="
echo "Staring Network experiment"
echo "==========================="
echo ""

echo "EXPERIMENT 1 -> Setup and teardown"
echo ""
# Run experiment solely on core 0
taskset -c 0 ./bin/server_conn 5000 &
sleep 2
taskset -c 1 ./bin/client_conn "127.0.0.1" 5000

echo ""
echo "EXPERIMENT 2 -> Bandwidth"
echo ""

echo ""
echo "==========================="
echo "Done Network experiment"
echo "==========================="
echo ""
