#!/bin/bash
echo clean cmake

if [ "$1" == "clean" ]; then
    echo remove cmake generate files without Makefile
    rm -rf CMakeFiles CMakeCache.txt cmake_install.cmake
elif [ "$1" == "fclean" ]; then
    echo remove all
    rm -rf CMakeFiles CMakeCache.txt cmake_install.cmake Makefile
fi