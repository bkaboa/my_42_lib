cmake_minimum_required( VERSION 3.16)

if (EXISTS ${CMAKE_SOURCE_DIR}/cmake_include/requirement.cmake)
    include(${CMAKE_SOURCE_DIR}/cmake_include/requirement.cmake)
else()
    message(FATAL_ERROR "requirement.cmake not found, in the cmake_include directory.")
endif()

option(TEST "Build all tests." OFF)
option(OPT_OPTION "Build the op library." OFF)
option(LOGGER_OPTION "Build the logger library." OFF)
option(GNL_OPTION "Build the gnl library." OFF)
option(SORT_OPTION "Build the sort library." OFF)

file(GLOB_RECURSE LIBFT_SRCS
    libft/*.c
)

file(GLOB_RECURSE SORT_SRCS
    sort/*.c
)

file(GLOB_RECURSE OPT_SRCS
    optLib/*.c
)

file(GLOB_RECURSE LOGGER_SRCS
    logger/*.c
)

file(GLOB_RECURSE GNL_SRCS
    gnl/*.c
)

project(
    ${PROJECT_NAME}
    VERSION ${VERSION}
    DESCRIPTION "my 42 project library"
    LANGUAGES C
)

set(CMAKE_C_FLAGS "-Wall -Wextra ")

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
target_include_directories(LIBFT
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/libft
)

if (LOGGER_OPTION)
    add_library(LOGGER STATIC ${LOGGER_SRCS})
    set_target_properties(LOGGER
        PROPERTIES 
            OUTPUT_NAME ${LIBLOGGER_NAME}
    )
    target_include_directories(LOGGER
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/logger
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/libft
    )
    target_compile_definitions(LOGGER
        PRIVATE
            # WRITE_LOG # replace printf functions with write function
            # FILE_LOG
    )
endif()

if (OPT_OPTION)
    add_library(LIBOPT STATIC ${OPT_SRCS})
    set_target_properties(LIBOPT
        PROPERTIES
            OUTPUT_NAME ${LIBOPT_NAME}
    )
    target_include_directories(LIBOPT
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/optLib
            ${CMAKE_CURRENT_LIST_DIR}/libft
            ${CMAKE_CURRENT_LIST_DIR}/logger
    )
endif()

if (SORT_OPTION)
    add_library(SORT STATIC ${SORT_SRCS})
    set_target_properties(SORT
        PROPERTIES
            OUTPUT_NAME ${LIBSORT_NAME}
    )
    target_include_directories(SORT
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/sort
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/libft
    )
endif()

if (GNL_OPTION)
    add_library(GNL STATIC ${GNL_SRCS})
    set_target_properties(GNL
        PROPERTIES
            OUTPUT_NAME ${LIBGNL_NAME}
    )
    target_include_directories(GNL
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/gnl
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/libft
            ${CMAKE_CURRENT_LIST_DIR}/logger
    )
endif()

if (TEST)
    enable_testing()
    add_subdirectory(tests)
endif()
