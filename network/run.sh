echo ""
echo "==========================="
echo "Staring Network experiment"
echo "==========================="
echo ""

echo "EXPERIMENT 1 -> Setup and teardown"
echo ""

BIN="./build/bin"

# Run experiment solely on core 0
taskset -c 0 $(BIN)/server_conn 5000 &
sleep 2
taskset -c 1 $(BIN)/client_conn "127.0.0.1" 5000

echo ""
echo "EXPERIMENT 2 -> Bandwidth"
echo ""
taskset -c 0 $(BIN)/server_bw 6000 &
sleep 3
taskset -c 1 $(BIN)/client_bw "127.0.0.1" 6000
echo ""

echo ""
echo "EXPERIMENT 3 -> RTT"
echo ""
$(BIN)/server_rtt "127.0.0.1" 7000 &
sleep 3
$(BIN)/client_rtt "127.0.0.1" 7000
echo ""

echo "==========================="
echo "Done Network experiment"
echo "==========================="
echo ""
