/*
 *  gerp.h
 *  Benjamin Silver and Joel MacVicar
 *  April 12, 2023
 *
 *  CS 15 Project 4 gerp
 *
 *  Purpose: Searches and indexes files for the client
 */

#ifndef __GERP_H__
#define __GERP_H__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "wordHash.h"
#include "FSTree.h"
#include "DirNode.h"

using namespace std;

class gerp {
public:
    void run(string directory, ofstream &output);

private:
    void getInfo(string word, wordHash &wh, ofstream &output, bool sensitive);
    void hashFiles(DirNode *curr, wordHash &wh, string path); 
    void queryLoop(ofstream &output, wordHash &wh); 
    void newOut(ofstream &oldOutput, string fileName);
    void noWord(ofstream &output, string word, bool sensitive);
    void recursive_find_FST(string path, DirNode *curr); 
};


#endif