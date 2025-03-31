cmake_minimum_required( VERSION 3.16)

if (EXISTS ${CMAKE_SOURCE_DIR}/cmake_include/requirement.cmake)
    include(${CMAKE_SOURCE_DIR}/cmake_include/requirement.cmake)
else()
    message(FATAL_ERROR "requirement.cmake not found, in the cmake_include directory.")
endif()

option(TEST "Build all tests." OFF)
option(OPT_OPTION "Build the op library." OFF)
option(LOGGER_OPTION "Build the logger library." OFF)

file(GLOB LIBFT_SRCS libft/*.c)

set(LIBROPT_SRCS
    optLib/ft_getopt.c
)

set(LOGGER_SRCS
    logger/ft_logger.c
)

project(
    ${PROJECT_NAME}
    VERSION ${VERSION}
    DESCRIPTION "my 42 project library"
    LANGUAGES C
)

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)

add_custom_target(
    create_dir ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
)

add_library(LIBFT STATIC ${LIBFT_SRCS})
set_target_properties(LIBFT
    PROPERTIES
        OUTPUT_NAME ${LIBFT_NAME}
)

if (OPT_OPTION)
    add_library(LIBOPT STATIC ${LIBROPT_SRCS})
    set_target_properties(LIBOPT
    PROPERTIES
        OUTPUT_NAME ${LIBOPT_NAME}
    )
    add_dependencies(LIBOPT LIBFT)
endif()

if (LOGGER_OPTION)
    add_library(LIB_LOGGER STATIC ${LOGGER_SRCS})
    set_target_properties(LIB_LOGGER
        PROPERTIES 
            OUTPUT_NAME ${LIBLOGGER_NAME}
    )
endif()
