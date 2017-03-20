#!/bin/bash

# create a large file
FILE="large_file"
if [ ! -f $FILE ]; then
	echo ""
	echo "large test file does not exist"
	echo "start creating a 10 GB test file (may take a few minutes)..."
	head -c 10737418240 < /dev/urandom > test_file
	echo "test file is created"
	echo ""
fi
