cmake_minimum_required(VERSION 3.16)

project(optLib
    VERSION 0.0.1
    DESCRIPTION "A library for cli option parsing"
    LANGUAGES C
)

add_library(optLib STATIC
    optLib.c
    optLib.h
)