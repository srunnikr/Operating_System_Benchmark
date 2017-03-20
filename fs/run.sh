#!/bin/bash

echo ""
echo "==========================="
echo "Starting File System experiment"
echo "==========================="
echo ""

# sudo taskset -c 0 nice -n -20 ./build/fs "$PWD/large_file"

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
	sudo taskset -c 0 nice -n -20 ./bin/fs "$PWD/testfiles/$file"
done

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
	sudo taskset -c 0 nice -n -20 ./bin/fs_seq_rand "$PWD/testfiles/$file"
done

echo ""
echo "==========================="
echo "Done File System experiment"
echo "==========================="
echo ""
