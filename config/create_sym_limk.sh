#!/bin/bash

# For each directory into srcs/
for dir in srcs/*;
do
    # Checks if dir is a directory
    if [ -d "$dir" ];
	then
        # Creates symlink for each .h file from includes
        for header_file in includes/*.h;
		do
            ln -s "../../$header_file" "$dir"
        done
    fi
done

