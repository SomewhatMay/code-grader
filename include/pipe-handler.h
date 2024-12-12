#pragma once 

#include <iostream>
#include <string>
#include <cstdlib>

//creating a struct to store the both streams for the pipe we want to create
struct Pipe {
    FILE* read;
    FILE* write;
};

/*

returns a pointer to a stream than can be used to read and write to the pipe, 

has two modes r for reading and w for writting, the function expects:

"write" or "read" for the respective pointer to the stream that it is creating 

*/
FILE* establish_pipe(std::string executable_name, std::string mode);

/*

takes in the pointer to the stream, and tries to read from it 

is expecting a stream that has reading mode enabled and will throw if it recieves a stream with type write

returns a string with what the program outputted

*/
std::string read_from_stream(FILE* stream);



/*

takes in the pointer to the stream, and tries to write to it 

is expecting a stream that has writting mode enabled and will throw if it recieves a stream with type read

returns nothing, simply will throw if the write was not successful 
*/
void write_to_stream(FILE* stream);


/*

closes any pipes that were opened previously

returns nothing, simply will throw if closing the pipe was not successful 

*/
void close_pipe(FILE* stream);