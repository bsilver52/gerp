/*
 *  hash.h
 *  Benjamin Silver
 *  April 12, 2023
 *
 *  CS 15 Project 4 gerp
 *
 *  Purpose: TODO
 */


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "hash.h"

using namespace std;


void hash::theHash(const string &input_file) {
    // open file
    ifstream input;
    openFile(input, input_file);
    string line;
    int i = 0;     // keeps track of line number 
    while (not getline(input, line).fail()) {
        i++;    // update line num
        stringstream ss = line; // convert back to stream to parse strings
        string s;
        while (ss >> s) {               // while stil words on the curr line
            if (load > loadFactor) {         // check if need to expand
                expand();
            }
            if (wordSearch(s)) {
                updateBucket(s,hashCompress(s))
            }

                // if exists, update the spot
                // if not
                else {
                    int index = hashCompress(s);   // hash, compress, and collision
                    insertHash(s, index, i, input_file);
                }
            
            // TODO
            // serarch for lowercase word
            // update for all perm if needed
        }
    }    
}

void hash::expand() {
    // saving curr state in temp
    vector<bucket> temp;
    temp = hashTable;
    // initializing hashTable with empty buckets 
    info emptyInfo;
    bucket empty = {false, emptyInfo};
    tableSize *= 2;
    hashTable.erase();
    for (int i = 0; i < tableSize; i++) {
        hashTable.push_back(empty);
    }
    // rehashing temp to hashTable with new tableSize
    for (int i = 0; i < temp.size(); i++) {
        if (temp[i].filled) {
            int index = hashCompress(temp[i].word.word);   // hash, compress, and collision
            hashTable[index].filled = true;
            hashTable[index].word.word = temp[i].word.word;
            for (int i = 0; i < )
            hashTable[index].word.lineNum[back()].push_back(lineNum);
            hashTable[index].word.locationFile.push_back(file);
        }
    }
 }

int hash::collisionHandle(int hashVal) {
    if (not hashTable[hashVal].filled) {
        return hashVal;
    } else {
        int next = hashVal++;
        while (hashTable[next].filled) {
            next++;
        }
        return next;
    }
}

 void hash::insertHash(string word, int index, int lineNum, string file) {
    hashTable[index].filled = true;
    hashTable[index].word.word = word;
    hashTable[index].word.lineNum[back()].push_back(lineNum);
    hashTable[index].word.locationFile.push_back(file);
 }

 bool hash::wordSearch(string word) {
    int tableSpot = hashCompress(word);

    while (hashTable[tableSpot].filled) {
        if (hashTable[tableSpot].word.word == word) {
            return true;
        }
        tableSpot++;
    }
    return false;
 }

 int hash::hashCompress(string word) {
    size_t hashValue = str_hash(word);
    int tableSpot = hashValue % tableSize;
    return collisionHandle(tableSpot);
    
 }

//  void hash::allPerm(string word) {
    
//     if (word == )
    
//     for (int i = 0; i < allPerm.size()) {
//         if (allPerm[i] == word) {
//             return;
//         }
//     }

//     allPerm.push_back(word);
//  }

 /*
 * name:      openFile
 * purpose:   to open files used by Zap
 * arguments: the file name and the desired stream 
 * returns:   none
 * effects:   will throw runtime_error if file cannot be opened
 */
template<typename streamtype>
void hash::openFile(streamtype &stream, string file_name) {
    stream.open(file_name);
    if (not stream.is_open()) {
        throw runtime_error("Unable to open file " + file_name);
    }     
}
 

 void hash::updateBucket() {

 }