#pragma once 

#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>


/*

input params: 
* input -> takes input string that you want to write to standard stream,
* program_name -> name of program to write to

purpose:
* writes to the standard stream of the program passed in
* returns the output from the standard stream of the program as a string 

Dependecies:
*assumes that the program is fully functional and doesnt segfault
*assumes that program is already compiled
*/
std::string process_program(std::string input, std::string program_name);


/*

input params:
* pipe -> takes in a pointer to the stream opened by the pipe

purpose:
* takes the data from the stream stores it in a buffer
* converts the buffer to an std::string then returns the string 

*/
std::string stream_pipe_data(FILE* pipe);