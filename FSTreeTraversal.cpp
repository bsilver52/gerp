/*
 *  FSTreeTraversal.cpp
 *  Benjamin Silver and Joel MacVicar
 *  April 12, 2023
 *
 *  CS 15 Project 4 Gerp
 *
 *  Purpose: TODO
 *
*/
#include "FSTree.h"
#include "DirNode.h"

#include <iostream>
#include <fstream>
#include <string>
#include <utility>

using namespace std;

void FSTreeTraversal(string dir); 
void recursive_find_FST(string path, DirNode *curr);

// TODO Function contracts
int main(int argc, char *argv[]) {
    if (argc != 2) {
        throw runtime_error("Usage: ./treeTraversal Directory");
    }
    else {
        string root = argv[1];
        FSTreeTraversal(root);
    }
    return 0;
}

void FSTreeTraversal(string dir) {
    // call constructer 
    FSTree fileTree(dir);
    DirNode *root = fileTree.getRoot();
    recursive_find_FST("", root);
}

void recursive_find_FST(string path, DirNode *curr) {
    path += curr->getName() + "/";

    // if has files 
    if (curr->hasFiles()) {
        for (int i = 0; i < curr->numFiles(); i++) {
            cout << path + curr->getFile(i) << endl;
        }
    }
    // if hassub dir
    if (curr->hasSubDir()) {
        for (int i = 0; i < curr->numSubDirs(); i++) {
            recursive_find_FST(path, curr->getSubDir(i));
        }
    }
}
