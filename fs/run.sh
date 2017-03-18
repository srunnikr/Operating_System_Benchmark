#!/bin/bash

echo ""
echo "Test for 1KB file"
./build/bin/fs "$PWD/testfiles/f1.txt"

echo ""
echo "Test for 2KB file"
./build/bin/fs "$PWD/testfiles/f2.txt"

echo ""
echo "Test for 4KB file"
./build/bin/fs "$PWD/testfiles/f4.txt"

echo ""
echo "Test for 8KB file"
./build/bin/fs "$PWD/testfiles/f8.txt"

echo ""
echo "Test for 16KB file"
./build/bin/fs "$PWD/testfiles/f16.txt"

echo ""
echo "Test for 32KB file"
./build/bin/fs "$PWD/testfiles/f32.txt"

echo ""
echo "Test for 64KB file"
./build/bin/fs "$PWD/testfiles/f64.txt"

echo ""
echo "Test for 128KB file"
./build/bin/fs "$PWD/testfiles/f128.txt"

echo ""
echo "Test for 256KB file"
./build/bin/fs "$PWD/testfiles/f256.txt"

echo ""
echo "Test for 512KB file"
./build/bin/fs "$PWD/testfiles/f512.txt"

echo ""
echo "Test for 1MB file"
./build/bin/fs "$PWD/testfiles/f1024.txt"

echo ""
echo "Test for 2MB file"
./build/bin/fs "$PWD/testfiles/f2048.txt"

echo ""
echo "Test for 4MB file"
./build/bin/fs "$PWD/testfiles/f4096.txt"
