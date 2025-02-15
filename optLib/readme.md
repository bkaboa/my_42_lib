# Option Management Library

## Overview

This library provides a set of functions to manage command-line options for C programs. It allows you to define, parse, and handle options with various types, including strings and long integers. The library also supports array options and provides functions to sanitize and debug the option list.

## Features

- Define main and additional options with descriptions.
- Parse command-line arguments and populate option values.
- Handle both single values and arrays of values.
- Sanitize the option list to remove unused options.
- Print help messages for defined options.
- Debug option list to inspect internal states.

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC or Clang)
- Standard C library

### Installation

1. Include the `optlib.h` header file in your project.
2. Compile the source file along with your project files.

### Usage

1. **Define Options**: Use `opt_set_main` to set the main option and `opt_add_new` to add additional options.

   ```c
   t_opt *options = NULL;
   opt_set_main(&options, OPT_STRING, "Main option description");
   opt_add_new("-s", "--short", OPT_STRING, "Short option description", 1, options);
   opt_add_new("-l", "--long", OPT_LONG, "Long option description", 2, options);
