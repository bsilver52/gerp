/*
 *  gerp.cpp
 *  Benjamin Silver and Joel MacVicar
 *  April 12, 2023
 *
 *  CS 15 Project 4 Gerp
 *
 *  Purpose: Allows the client to locaten instances of word for the files in a
 *  root directory
 */

#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include "gerp.h"
#include "stringProcessing.h"

using namespace std;

// run
// Input: A root directory and output file stream
// Description: Runs the gerp search program by indexing a set of files and
// searching its contents
// Output: Nothing (void function)
void gerp::run(string directory, ofstream &output) {
    // build the index
    FSTree fileTree(directory);
    DirNode *root = fileTree.getRoot();
    wordHash wh;
    string s;
    hashFiles(root, wh, s);
    
    //perform queries
    queryLoop(output, wh);
    cout << "Goodbye! Thank you and have a nice day." << endl;
}

// hashFiles
// Input: A file tree root, hash table object, and empty file path string
// Description: Hashes all the files contained in a root directory
// Output: Nothing, but the contents of each file are added to the hash
// table when appropriate
void gerp::hashFiles(DirNode *curr, wordHash &wh, string path) {
    path += curr->getName() + "/";
    
    //directory has files
    if (curr->hasFiles()) {
        for (int i = 0; i < curr->numFiles(); i++) {
            string fileName = curr->getFile(i);
            wh.theHash(path + fileName);
        }
    }

    //directory has folders
    if (curr->hasSubDir()) {
        for (int j = 0; j < curr->numSubDirs(); j++) {
            hashFiles(curr->getSubDir(j), wh, path);
        }
    }
}

// queryLoop
// Input: An output file stream and reference to a hash table object
// Description: Prompts the client for words for the duration of the program
// Output: Nothing, but information is printed to the output file on each
// iteration of the loop
void gerp::queryLoop(ofstream &output, wordHash &wh) {
    string firstCommand, secondCommand, trimmed; // is this an unused variable
    cout << "Query? ";
    
    while (cin >> firstCommand) {
        if (firstCommand == "@q" or firstCommand == "@quit") {
            return;
        }

        //insensitive query
        if (firstCommand == "@i" or firstCommand == "@insensitive") {
            cin >> secondCommand;
            getInfo(secondCommand, wh, output, false);
        //change output file
        } else if (firstCommand == "@f") {
            cin >> secondCommand;
            newOut(output, secondCommand);
        //new output file stream
        } else {
            getInfo(firstCommand, wh, output, true);
        }
        cout << "Query? ";
    }
}

// getInfo
// Input: A word to search for, reference to a hash table object, output
// file stream, and the query type (sensitive/insensitive)
// Description: Retrieves information for a given word query from all of the
// files it occureces in
// Output: Nothing (void function)
void gerp::getInfo(string word, wordHash &wh, 
                   ofstream &output, bool sensitive) {
    stripNonAlphaNum(word);
    int index = wh.wordSearch(word);

    // case senstive 
    if (not sensitive) {
        lowerCase(word); 
    }
    // word does not exist in directory
    if (wh.wordSearch(word) == -1) {
        noWord(output, word, sensitive);
        return;
    }

    //print output information
    if (sensitive) {
        wh.sensitiveOutput(index, output, sensitive);
    }
    else {
        wh.insensitiveOutput(index, output);
    }
}

// noWord
// Input: An output file stream, a word to search for, and the query type
// (sensitive/insensitive)
// Description: Prints a message to the output file when no instances of a
// query are found
// Output: Nothing, but the appropriate information is sent to the output file
void gerp::noWord(ofstream &output, string word, bool sensitive) {
    output << word << " Not Found.";
    
    if (sensitive) {
        output << " Try with @insensitive or @i." << endl;
    } else {
        output << endl;
    }
}

// newOut
// Input: The initial output file stream and a new file name to write to
// Description: Changes the output stream to a file specified by the client
// Output: Nothing (void function)
void gerp::newOut(ofstream &oldOutput, string fileName) {
    ofstream newOutput(fileName);
    newOutput.open(fileName);
    newOutput.rdbuf();
    oldOutput.close();
}