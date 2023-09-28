/*
 *  main.cpp
 *  Benjamin Silver and Joel MacVicar
 *  April 12, 2023
 *
 *  CS 15 Project 4 Gerp
 *
 *  Purpose: Provide the client a driver file to run Gerp
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "gerp.h"

using namespace std;

template<typename streamtype>
void fileOpener(streamtype &stream, const string filename);

// main
// Input: The number of command arguments and their names
// Description: Runs the zap compressors and uncompressors
// Output: Returns 0
int main(int argc, char *argv[]) {
    // if incorrect # of args
    if (argc != 3) {
        cerr << "Usage: ./gerp inputDirectory outputFile" << endl;
        return EXIT_FAILURE;
    }

    ofstream outstream;
    fileOpener(outstream, argv[2]);
    gerp program;
    program.run(argv[1], outstream);
    outstream.close();
    return 0;
}

// fileOpener
// Input: A file stream and its corresponding name
// Description: Checks if a file can be opened
// Output: Nothing, but a runtime is thrown if the file cannot open
template<typename streamtype>
void fileOpener(streamtype &stream, const string filename) {
    stream.open(filename);
        
    if (not stream.is_open()) {
        throw runtime_error("Unable to open file " + filename);
    }
}