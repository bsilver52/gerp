/*
 *  hash.h
 *  Benjamin Silver
 *  April 12, 2023
 *
 *  CS 15 Project 4 gerp
 *
 *  Purpose: TODO
 */

#ifndef __HASH_H__
#define __HASH_H__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class hash {
public:
    void theHash(const string &input_file);
    bool wordSearch(string word);

private:
    vector<bucket> hashTable;
    int numElem;
    int tableSize;
    int load = numElem / tableSize;
    static const int loadFactor = 0.7;

// NOTE: WHERE DO WE PUT THESE STRUCTS SYTLE
struct info {
    string word; //handled
    vector<string> locationFile;
    vector<vector<int>> lineNum; //handled
    vector<string> allPerm; //will handle later
}
struct bucket {
    bool filled; //handled
    info word;
}

    // open 
    template<typename streamtype>
    void openFile(streamtype &stream, string file_name);
    
    // expand 
    void expand();
    // hash and compress

    // handle collision to find the true index
    int collisionHandle(int hashVal);
    int hashCompress(string word);


    // insert into the table
    void insertHash(string word, int index, int lineNum, string file);
    void outputInfo(int index, ostream &output);
    // update perm vector 

};


#endif