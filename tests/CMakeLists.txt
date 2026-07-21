set(TEST_INCLUDE_DIRS
	${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/tests
	${CMAKE_SOURCE_DIR}/libft
)

function(add_libft_test test_name)
	add_executable(${test_name} ${test_name}.c)
	target_include_directories(${test_name} PRIVATE ${TEST_INCLUDE_DIRS})
	target_link_libraries(${test_name} PRIVATE LIBFT)
	set_target_properties(${test_name}
		PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
	)
	add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

set(LIBFT_TESTS
	test_ft_is
	test_ft_string
	test_ft_memory
	test_ft_convert
)

foreach(test_name ${LIBFT_TESTS})
	add_libft_test(${test_name})
endforeach()

if (OPT_OPTION)
	add_executable(test_optlib test_optlib.c)
	target_include_directories(test_optlib PRIVATE ${TEST_INCLUDE_DIRS})
	target_link_libraries(test_optlib PRIVATE LIBOPT LIBFT)
	set_target_properties(test_optlib
		PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
	)
	add_test(NAME test_optlib COMMAND test_optlib)
endif()

if (LOGGER_OPTION)
	add_executable(test_logger test_logger.c)
	target_include_directories(test_logger PRIVATE ${TEST_INCLUDE_DIRS})
	target_link_libraries(test_logger PRIVATE LIB_LOGGER LIBFT)
	set_target_properties(test_logger
		PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
	)
	add_test(NAME test_logger COMMAND test_logger)
endif()

if (GNL_OPTION)
	add_executable(test_gnl test_gnl.c)
	target_include_directories(test_gnl PRIVATE ${TEST_INCLUDE_DIRS})
	target_link_libraries(test_gnl PRIVATE LIB_GNL LIBFT)
	set_target_properties(test_gnl
		PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
	)
	add_test(NAME test_gnl COMMAND test_gnl)
endif()

message(STATUS "Unit tests enabled (CTest). Run: ctest --test-dir ${CMAKE_BINARY_DIR}")
