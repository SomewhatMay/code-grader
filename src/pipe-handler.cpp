#include "pipe-handler.h"
#include "globals.h"

std::string stream_pipe_data(FILE* pipe){

    //creates buffer that can be dynamically resized 
    size_t buffer_size = globals::DEFAULT_BUFFSZ;
    char* buffer = new char[buffer_size];  
    size_t current_pos = 0; 

    //reads data from pipe into buffer
    while (fgets(buffer + current_pos, buffer_size - current_pos, pipe)) {

        current_pos += strlen(buffer + current_pos);  

        //reallocs memory when buffer size is too small 
        if (current_pos >= buffer_size - 1) { 

            buffer_size *= 2;  
            char* temp = static_cast<char*>(realloc(buffer, buffer_size));
            
            // Handle memory allocation failure
            if (!temp) {
                std::cerr << "Memory allocation failed! char buffer to read from pipe was unable to be expanded" << std::endl;
                delete[] buffer; 
                return "";  
            }

            buffer = temp;
        }
    }

  
    std::string stream = std::string(buffer); 

    delete[] buffer;  
    
    return stream;

}

std::string process_program(std::string input, std::string program_name) {

    // Will be used to feed in input string to the program
    std::string command = "echo " + input + " | ./" + program_name;
   

    // Opens up a pipe to the selected program
    FILE *pipe = popen(command.c_str(), "r");


    //checks to see if pipe was opened correctly, if not throw an error 
    if (!pipe) {
        std::cerr << "Critical pipe failure: unable to establish pipe between parent and child processes\n";
        return "";
    }

    //gets data from stream
    std::string output = stream_pipe_data(pipe);
    
    //deallocs pipe 
    fclose(pipe);


    return output;
}
