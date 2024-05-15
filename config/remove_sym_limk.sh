#!/bin/bash

target_dir="includes"

for symlink_file in $target_dir/*;
do
    # Checks if the file is a symlink
    if [ -L "$symlink_file" ];
	then
        rm "$symlink_file"
    fi
done

# --------------------
# Removes symlinks from srcs/*/
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
