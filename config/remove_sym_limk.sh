#!/bin/bash

dirs="srcs/*"
dirs="$dirs srcs/.test"

# For each directory into srcs/
for dir in $dirs;
do
    # Checks if dir is a directory
    if [ -d "$dir" ];
	then
        # Remove symlink from dir
		rm -f $dir/*.h
    fi
done

