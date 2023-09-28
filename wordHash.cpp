/*
 *  wordhash.cpp
 *  Benjamin Silver and Joel MacVicar
 *  April 12, 2023
 *
 *  CS 15 Project 4 gerp
 *
 *  Purpose: Hashes the words in a file in order for the client to perform
 *  word queries
 */


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <cassert>
#include "wordHash.h"
#include "stringProcessing.h"

using namespace std;

// wordHash (constructor)
// Input: Nothing
// Description: Initializes the member variable for the hash table class
// Output: Nothing, but the hash table is prepared for word insertion
wordHash::wordHash() {
    numElem = 0;
    tableSize = 50;
    load = 0;
    bucket empty;
    empty.filled = false;
    for (int i = 0; i < tableSize; i++) {
        hashTable.push_back(empty);
    }
}

// theHash
// Input: An input file string
// Description: HAshes all words in a file that have not been previously seen
// Output: Nothing, but the hash table is updated accordingly
void wordHash::theHash(const string &input_file) {
    ifstream input;
    openFile(input, input_file);
    string line;
    int i = 0;

    while (getline(input, line)) {
        i++;
        stringstream ss; 
        ss << line;
        string s;

        while (ss >> s) {
            stripNonAlphaNum(s);
            if (load > loadFactor) {
                expand();
            }
            if (s.empty()) {
                continue;
            } else {
                if (wordSearch(s) == -1) {
                    insertNew(s, hashCompress(s), i, input_file);
                } else {
                    updateBucket(wordSearch(s), i, input_file);
                }
            }
        }
    }
    input.close();
}

// expand
// Input: Nothing
// Description: Expands the hash table and rehashes its current contents when
// the load factor is exceeded
// Output: Nothing, but the hash table is updated accordingly
void wordHash::expand() {
    // saving curr state in temp
    vector<bucket> temp;
    temp = hashTable;
    // initializing hashTable with empty buckets 
    bucket empty;
    empty.filled = false;
    // doubling table wsize and updating load 
    tableSize *= 2;
    float numElemFloat = numElem * 1.0;
    load = numElemFloat / tableSize;
    hashTable.clear();
    for (int i = 0; i < tableSize; i++) {
        hashTable.push_back(empty);
    }
    // rehashing temp to hashTable with new tableSize
    int tempSize = temp.size();
    for (int i = 0; i < tempSize; i++) {
        if (temp[i].filled) {
            // rehash, compress, and collision
            int index = hashCompress(temp[i].word); 
            // reassigning 
            hashTable[index].filled = true;
            hashTable[index].word = temp[i].word;
            hashTable[index].lineNum = temp[i].lineNum;
            hashTable[index].locationFile = temp[i].locationFile;
            hashTable[index].allPerm = temp[i].allPerm;
        }
    }
 }

// collisionHandle
// Input: The hash value of a word
// Description: Finds the first open position in a table from a hashed value
// Output: An integer, representing an open table position
int wordHash::collisionHandle(int hashVal) {
    // if the slot is empty 
    if (not hashTable[hashVal].filled) {
        return hashVal;
    } else {
        int next = hashVal++;
        // move down the table to find next open spot
        
        while (hashTable[next].filled) {
            next++;
            // if reached end of the vector loop to begining
            if (next == tableSize) {
                next = 0;
            }
        }
        return next;
    }
}

// insertNew
// Input: A word from a file, the position to insert at, its line number in
// the file, and its file location 
// Description: Inserts a word into the hash table upon its first occurence in
// a file 
// Output: Nothing, but the hash table is updated appropriately
void wordHash::insertNew(string &word, int index, int &line, string file) {
    numElem++;
    float numElemFloat = numElem * 1.0;
    load = numElemFloat / tableSize;
   
    // update hash table with new info 
    hashTable[index].filled = true;
    hashTable[index].word = word;
    vector<int> temp;
    temp.push_back(line);
    hashTable[index].lineNum.push_back(temp);
    hashTable[index].locationFile.push_back(file);
    // updating our perm vector
    perm(word); 
}

// wordSearch
// Input: A word to search for
// Description: Determine if a word is present in the hash table 
// Output: The word's position in the hash table, or -1 if it is not present
int wordHash::wordSearch(const string &word) {
    // getting hash value for word and compressing    
    size_t hashValue = hash<string>{}(word);
    int tableSpot = hashValue % tableSize;
    
    // looping till empty bucket is encountered
    while (hashTable[tableSpot].filled) {
        // if the word is encountered
        if (hashTable[tableSpot].word == word) {
            return tableSpot;
        }
        tableSpot++;
        // if reached end of the vector loop to beginning
        if (tableSpot == tableSize) {
            tableSpot = 0;
        }
    }
    // if the word is not in hash, return sentinel -1
    return -1;
}

// hashCompress
// Input: A word from a file
// Description: Determines where in the hash table to insert a word 
// Output: An integer, representing a table position

int wordHash::hashCompress(string word) {
    size_t hashValue = hash<string>{}(word);
    int tableSpot = hashValue % tableSize;
    return collisionHandle(tableSpot);
}

// openFile
// Input: A file stream and its corresponding name
// Description: Checks if a file can be opened
// Output: Nothing (void function)
template<typename streamtype>
void wordHash::openFile(streamtype &stream, string file_name) {
    stream.open(file_name);
    if (not stream.is_open()) {
        throw runtime_error("Unable to open file " + file_name);
    }
}
 
// updateBucket
// Input: The possition in the hash table to update, and the new line/file
// information from a word's repeat occurence
// Description: Updates a words hash table information upon encountering
// multiple instance of a word
// Output: An integer, representing an open table position
void wordHash::updateBucket(int index, int &line, string file) {
    // cases where word occurs in a file for first time or the hashed lowercase
    // version of a word has not ocurred yet
    if ((hashTable[index].locationFile.empty()) or 
        (hashTable[index].locationFile.back() != file )) {

        hashTable[index].locationFile.push_back(file);

        vector<int> temp;
        temp.push_back(line);
        hashTable[index].lineNum.push_back(temp);
    //word has already occurred in the file
    } else {
        // push line number into list if word has not ocurred in the line yet
        if (hashTable[index].lineNum.back().back() != line) {
            int i = hashTable[index].lineNum.size() - 1;
            hashTable[index].lineNum[i].push_back(line);
        } 
    }
}

// perm
// Input: A string for a word in the hash table
// Description: updates the allPerm vector at the lowercase version
// of the word 
// Output: Nothing, void function
// Note: creates a lowercase version of the word if the nonlowercase
// version is encounterd first
void wordHash::perm(string &s) {
    string og = s;
    lowerCase(s);

    // if the lowercase version not in table yet
    if (wordSearch(s) == -1) {
        int index = hashCompress(s);
        numElem++;
        load = numElem / tableSize;
        hashTable[index].word = s;
        hashTable[index].filled = true;
        hashTable[index].allPerm.push_back(og);
    // the lowercase verson exists
    } else {
        int index = wordSearch(s);
        hashTable[index].allPerm.push_back(og);
    }
}


// sensitiveOutput
// Input: A word's hash table index, an output file stream, and the query
// type (sensitive/insensitive)
// Description: Writes the appropriate information to an output file for the
// case sensitive query 
// Output: Nothing, but the output file is updated appropriately
// Note: The query type is an input because this function is called by
// insensitiveOutput
void wordHash::sensitiveOutput(int index, ofstream &output, bool sensitive) {
    
    int numFiles = hashTable[index].locationFile.size();
    
    //iterate over all the line instances for each file occurences
    for (int i = 0; i < numFiles; i++) {
        int numLines = hashTable[index].lineNum[i].size();
        for (int j = 0; j < numLines; j++) {
            int lineNum = hashTable[index].lineNum[i][j];
            string file = hashTable[index].locationFile[i];

            //only print when the instance has not occurred in the line
            if (not findDups(lineNum, file, sensitive)) {
                string lineText = findLine(lineNum, file);
                output << file << ":" << lineNum << ": " << lineText << endl;
            }

        }
    }
}

// insensitiveOutput
// Input: A word's hash table index and an output file stream
// Description: Writes the appropriate information to an output file for the
// case insensitive query 
// Output: Nothing, but the output file is updated appropriately
void wordHash::insensitiveOutput(int index, ofstream &output) {
    // looping over all perms of the word
    int permSize = hashTable[index].allPerm.size();
    for (int i = 0; i < permSize; i++) {
        sensitiveOutput(wordSearch(hashTable[index].allPerm[i]), output, false);
    }

    findRepeat.clear();
}

// findLine
// Input: A file and a line number within it
// Description: Returns the text at given line number
// Output: A string, representing the text
string wordHash::findLine(int fileLine, string fileName) {
    ifstream input;
    string text;
    openFile(input, fileName);
    
    //iterate until reaching the line
    for (int i = 0; i < fileLine; i++) {
        getline(input, text);
    }
    input.close();
    return text;
}

// findDups
// Input: The line number/file of a word occurence and the query type
// (sensitive/insensitve)
// Description: Identifies instances where 2 case insensitive occurences of a
// occur on the same line
// Output: True if duplicates are found for the insensitive query, false if
// not
bool wordHash::findDups(int lineNum, string file, bool sensitive) {
    if (sensitive) {
        return false;
    }

    int repeatSize = findRepeat.size();
    //check each instance of the word
    for (int i = 0; i < repeatSize; i++) {
        if (findRepeat[i].first == file and findRepeat[i].second == lineNum) {
            return true;
        }
    }

    pair<string, int> newEntry = {file, lineNum};
    findRepeat.push_back(newEntry);

    return false;
}

// printTable
// Input: Nothing
// Description: Prints the contents of a hash tab
// Output: Nothing, but the table information is printed to cout
// Note: This was a public testing function that has been made private.
void wordHash::printTable() {
    // loop through entire hash table 
    for (int i = 0; i < tableSize; i++) {
        // if there is a word in the bucket 
        if (hashTable[i].filled) {
            // print the word at the index
            cout << "Printing word at index " << i << ": " 
                << hashTable[i].word << endl;
            cout << "SIZE = " << hashTable[i].allPerm.size() << endl;
            if (not hashTable[i].allPerm.empty()) {
                cout << "Here are all the perms:" << endl;
                int permSize = hashTable[i].allPerm.size();
                for (int g = 0; g < permSize; g++) {
                    cout << hashTable[i].allPerm[g] << endl;
                }
            }
            int numFiles = hashTable[i].locationFile.size();
            // for each location file
            for (int k = 0; k < numFiles; k++) {
                cout << hashTable[i].word << " occurs in file " 
                    << hashTable[i].locationFile[k]
                    << " at lines (";
                // for each line it occurs in for that file
                int numLines = hashTable[i].lineNum[k].size();
                for (int j = 0; j < numLines; j++) {
                    cout << hashTable[i].lineNum[k][j] << " ";
                }
                cout << ")" << endl;
            }
        }
    }
 }
