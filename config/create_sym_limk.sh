#!/bin/bash

dirs="srcs/*"
dirs="$dirs srcs/.test"

# For each directory into srcs/
for dir in $dirs;
do
	# Checks if dir is a directory
    if [ -d "$dir" ];
	then
        # Creates symlink for each .h file from includes
        for header_file in includes/*.h;
		do
            ln -sf "../../$header_file" "$dir"
        done
    fi
done

