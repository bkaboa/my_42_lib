cmake_minimum_required( VERSION 3.16)

if (EXISTS ${CMAKE_SOURCE_DIR}/cmake_include/requirement.cmake)
    include(${CMAKE_SOURCE_DIR}/cmake_include/requirement.cmake)
else()
    message(FATAL_ERROR "requirement.cmake not found, in the cmake_include directory.")
endif()

option(TEST "Build all tests." OFF)
option(OPT_OPTION "Build the op library." OFF)
option(LOGGER_OPTION "Build the logger library." OFF)

set ( LIBFT_FILES
    libft/ft_atoi.c
    libft/ft_is.c
    libft/ft_memcmp.c
    libft/ft_memcpy.c
    libft/ft_memset.c
    libft/ft_putchar.c
    libft/ft_putstr.c
    libft/ft_realloc.c
    libft/ft_strcat.c
    libft/ft_strcmp.c
    libft/ft_strdup.c
    libft/ft_strjoin.c
    libft/ft_strlen.c
    libft/ft_swap.c
    libft/ft_to.c
)

set( LIBROPT_FILES
    optLib/ft_getopt.c
)

set( LOGGER_FILES
    logger/ft_logger.c
)

project(
    ${PROJECT_NAME}
    VERSION ${VERSION}
    DESCRIPTION "my 42 project library"
    LANGUAGES C
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)

add_library(LIBFT STATIC ${LIBFT_FILES})
set_target_properties(LIBFT
    PROPERTIES
        OUTPUT_NAME ${LIBFT_NAME}
)

if (OPT_OPTION)
    add_library(LIBOPT STATIC ${LIBROPT_FILES})
    set_target_properties(LIBOPT
    PROPERTIES
        OUTPUT_NAME ${LIBOPT_NAME}
    )
    add_dependencies(LIBOPT LIBFT)
endif()

if (LOGGER_OPTION)
    add_library(LIB_LOGGER STATIC ${LOGGER_FILES})
    set_target_properties(LIB_LOGGER
    PROPERTIES 
        OUTPUT_NAME ${LIBLOGGER_NAME}
    )
endif()
