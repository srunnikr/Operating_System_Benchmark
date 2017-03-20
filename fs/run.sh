#!/bin/bash

echo ""
echo "==========================="
echo "Starting File System experiment"
echo "==========================="
echo ""

# Part 1 test buffer cache size
sudo taskset -c 0 nice -n -20 ./build/bin/fs_cache "$PWD/large_file"

# Part 2 test sequential and random read
for file in `ls -S -r $PWD/testfiles`
do
	# extract the size from file name
	name=`basename $file`
	name=${name%.*}
	name=${name#f}
	size=$name

	# test each file
	echo ""
	echo "Test for $size file"
	sudo taskset -c 0 nice -n -20 ./build/bin/fs_seq_rand "$PWD/testfiles/$file"
done

# Part 3 test contention
for i in `seq 1 20`
do
	echo "test $i processes run concurrently..."
	./fs_con.sh $i
done
