#!/bin/bash

echo "Updating and installing submodules and libraries."

# Check if catch2 is installed
if ! dpkg -s catch2 >/dev/null 2>&1; then
    echo "\e[31mFATAL: catch2 is not installed. Please run 'sudo apt install catch2' to install it."
    exit 1
fi

git submodule update --init --recursive

echo "\033[0;32mProject successfully set up."