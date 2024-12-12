cmake_minimum_required(VERSION 3.10)

project(code-grader)

# Add the executables
add_executable(
	code-grader
	src/main.cpp
	src/file-input.cpp
	src/pipe-handler.cpp
)

target_include_directories(
	code-grader
	PUBLIC
	${CMAKE_SOURCE_DIR}/include
)