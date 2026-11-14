#!/bin/bash

# Instead of looking at the README.md everytime, use this script.

read -rp "rebuild? (0/1):" rebuild
read -rp "run example? (0/1):" runit
read -rp "debug? (0/1):" debug

BUILD_TYPE="Release"
BUILD_DIR="cmake-build-release"

if [ "$debug" -eq 1 ]; then
    BUILD_TYPE="Debug"
    BUILD_DIR="cmake-build-debug"
fi

CMAKE=$(which cmake)
NINJA=$(which ninja)

# Configure it first
# The below already creates the directory if it doesn't yet exist
$CMAKE -G Ninja -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_MAKE_PROGRAM="$NINJA" -S . -B $BUILD_DIR

# Primarily used in pre-production build, cache elimination, cmakelists updates
if [ "$rebuild" -eq 1 ]; then
	$CMAKE --build $BUILD_DIR --target clean -j 4
fi

$CMAKE --build $BUILD_DIR --target all -j 4

if [ "$runit" -eq 1 ]; then
	for f in $(ls cmake-build*/*_example); do
		echo "Running "$f"...";
		./$f
	done
fi

if [ "$debug" -eq 1 ]; then
	for f in $(ls cmake-build-debug*/*_example); do
		echo "Debugging "$f"...";
		gdb ./$f
	done
fi
