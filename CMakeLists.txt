cmake_minimum_required(VERSION 3.10)

project(code-grader)

option(ENABLE_TESTS "Enable test build" ON)

if (ENABLE_TESTS)
	# Add Google Test as a submodule
	set(GOOGLETEST_PATH ${CMAKE_SOURCE_DIR}/external/googletest)
	add_subdirectory(${GOOGLETEST_PATH} ${CMAKE_BINARY_DIR}/googletest-build)

	# Add the test executable
	add_executable(
		code-grader-tests

		src/file-input/parser.cpp
		src/file-input/file-retriever.cpp

		tests/file-input/parser.cpp
	)

	target_include_directories(
		code-grader-tests
		PUBLIC
		${CMAKE_SOURCE_DIR}/include
	)

	# Link Google Test
	target_link_libraries(code-grader-tests gtest gtest_main)

	enable_testing()
	add_test(NAME code-grader-tests COMMAND code-grader-tests)
else()
	# Add the executables
	add_executable(
		code-grader
		src/main.cpp
		src/file-input/parser.cpp
		src/file-input/file-retriever.cpp
	)

	target_include_directories(
		code-grader
		PUBLIC
		${CMAKE_SOURCE_DIR}/include
	)
endif()