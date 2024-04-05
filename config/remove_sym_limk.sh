#!/bin/bash

# For each directory into srcs/
for dir in srcs/*;
do
    # Checks if dir is a directory
    if [ -d "$dir" ];
	then
        # Remove symlink from dir
		rm -f $dir/*.h
    fi
done

