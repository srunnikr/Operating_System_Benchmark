#!/bin/bash

num=$(($1 - 1))

if [ ! $num -eq 0 ]
then
	for i in `seq 1 $num`
	do
		name1="f64MB_"
		name2=$i
		name3=".txt"
		name=$name1$name2$name3
		echo "start process $i, reading file $name"
		sudo taskset -c 0 nice -n -20 ./build/bin/fs_con "$PWD/testfiles_con/$name" 0 &
	done
fi

# start process 0, which will print time
echo "start process 0, reading file f64MB_0.txt"
sudo taskset -c 0 nice -n -20 ./build/bin/fs_con "$PWD/testfiles_con/f64MB_0.txt" 1 &

PID=$!
echo "wait last process: PID = $PID"
wait $PID
echo "finish waiting"
echo ""
