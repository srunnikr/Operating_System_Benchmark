#!/bin/bash

# create a large file
FILE="large_file"
if [ -f $FILE ]; then
	echo "remove old test file..."
	rm large_file
fi
	
echo "start creating a large test file (may take a few minutes)..."
# create a 5G file
#head -c 5368709120 < /dev/urandom > large_file
# create a 10G file
head -c 10737418240 < /dev/urandom > large_file
echo "large file is created"
echo ""
