/*
 *  wordHash.h
 *  Benjamin Silver and Joel MacVicar
 *  April 12, 2023
 *
 *  CS 15 Project 4 gerp
 *
 *  Purpose: Stores the hash table necessary for indexing query information
 */

#ifndef __WORDHASH_H__
#define __WORDHASH_H__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class wordHash {
    public:

        wordHash(); //constructor
        void theHash(const string &input_file);
        int wordSearch(const string &word);
        void sensitiveOutput(int index, ofstream &output, bool sensitive);
        void insensitiveOutput(int index, ofstream &output);

    private:

    //variables
    struct bucket {
        bool filled;
        string word;
        vector<string> locationFile;
        vector<vector<int>> lineNum;
        vector<string> allPerm;
    };

        vector<bucket> hashTable;
        vector<pair<string, int>> findRepeat;
        
        int numElem;
        int tableSize;
        float load;
        const float loadFactor = 0.7;

        //methods
        template<typename streamtype>
        void openFile(streamtype &stream, string file_name);
        void expand();
        int hashCompress(string word);
        int collisionHandle(int hashVal);
        void insertNew(string &word, int index, int &line, string file);
        void updateBucket(int index, int &line, string file);
        void perm(string &s);
        string findLine(int fileLine, string fileName);
        bool findDups(int lineNum, string file, bool sensitive);
        void printTable(); //testing function
};

#endif