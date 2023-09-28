/*
 *  unit_tests.h
 *  Ben Silver and Joel MacVicar 
 *  April 12, 2023
 *
 *  CS 15 Project 4 Gerp
 *
 *  Purpose: Tests the functionality of the stringProcessing functions and hash
 *  table creation for single files/entire directories
 */

#include <cassert>
#include <sstream>

#include "stringProcessing.h"
#include "wordHash.h"
#include "FSTree.h"
#include "DirNode.h"
#include "gerp.h"

using namespace std;

////////////////////////////////////////////////////
//          stringProcessing.h tests              //
////////////////////////////////////////////////////

void trimNonAlpha() {
    string testString = "!!!--#test24^^^";
    string clean = stripNonAlphaNum(testString);
    assert(clean == "test24");
}


void null_after_cut() {
    string testString = "!!!%(*)*))~)@)";
    string clean = stripNonAlphaNum(testString);
    assert(clean == "");
}

void noTrim() {
    string testString = "fejhehwjejrornfsnfdfoiurehjndaslsklas";
    string clean = stripNonAlphaNum(testString);
    assert(clean == "fejhehwjejrornfsnfdfoiurehjndaslsklas");
}

////////////////////////////////////////////////////
//                wordHash.h tests                //
////////////////////////////////////////////////////

// running on one file 


void multword_norepeat() {
    wordHash wh;
    string file = "tinyFile.txt";

    wh.theHash(file);
    wh.printTable();

   assert(wh.wordSearch("Here") != -1);
}




void multipleLine() {
    wordHash wh;
    string file = "multipleLine.txt";

    wh.theHash(file);
    wh.printTable();
}


// ////////////////////////////////////////////////////
// //                   gerp.h tests                 //
// ////////////////////////////////////////////////////

void multiFile() {
    string directory = "proj4-test-dirs/tinyData";
    FSTree fileTree(directory);
    DirNode *root = fileTree.getRoot();
    wordHash wh;
    string s;
    gerp gerpy;
    // recursive loop to hash all files under a root
    gerpy.hashFiles(root, wh, s);
    assert(wh.wordSearch("excited") != -1);
    // wh.printTable();
}
