#!/bin/bash

# Instead of looking at the README.md everytime, use this script.

read -rp "rebuild? (0/1):" rebuild
read -rp "run example? (0/1):" runit

CMAKE=$(which cmake)
NINJA=$(which ninja)

# Configure it first
# The below already creates the directory if it doesn't yet exist
$CMAKE -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=$NINJA -G Ninja -S . -B cmake-build-release

# Primarily used in pre-production build, cache elimination, cmakelists updates
if [ "$rebuild" -eq 1 ]; then
	$CMAKE --build cmake-build-release --target clean -j 4
fi

$CMAKE --build cmake-build-release --target all -j 4

if [ "$runit" -eq 1 ]; then
	for f in $(ls cmake-build*/*_example); do
		echo "Running "$f"...";
		./$f
	done
fi

