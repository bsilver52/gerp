/*
 *  stringProcessing.h
 *  Benjamin Silver
 *  April 12, 2023
 *
 *  CS 15 Project 4 gerp
 *
 *  Purpose: Parses strings for the wordHash and gerp classes
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void stripNonAlphaNum(string &input); 
bool isAlphaNum(char &stringChar);
void lowerCase(string &s);
