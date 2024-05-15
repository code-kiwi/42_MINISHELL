#!/bin/bash

# --------------------
# Creates symlinks into includes/ from each header into libft/includes/
targetdir="includes"

for header_file in libft/includes/*.h;
do
	ln -sf "../$header_file" "$targetdir"
done

# --------------------
# Creates symlinks into srcs/, from each header file into includes/
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
