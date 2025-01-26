cmake_minimum_required( VERSION 3.16)

if (EXISTS ${CMAKE_SOURCE_DIR}/cmake_include/requirement.cmake)
    include(${CMAKE_SOURCE_DIR}/cmake_include/requirement.cmake)
else()
    message(FATAL_ERROR "requirement.cmake not found, in the cmake_include directory.")
endif()

option(TEST "Build all tests." OFF)
option(OPTLIB "Build the op library." OFF)

set ( LIBFT_FILES
    libft/ft_putchar.c
    libft/ft_putstr.c
    libft/ft_strlen.c
)

set ( OPT_FILES
    optLib/ft_getopt.c
)

project(
    ${PROJECT_NAME}
    VERSION ${VERSION}
    DESCRIPTION "my 42 project library"
    LANGUAGES C
)

add_library(${LIBFT} STATIC ${LIBFT_FILES})

if (OPTLIB)
    add_library(${OPT_LIB} STATIC ${OPT_FILES})
endif()