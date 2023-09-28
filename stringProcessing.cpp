/*
 *  stringProcessing.cpp
 *  Benjamin Silver and Joel MacVicar
 *  April 12, 2023
 *
 *  CS 15 Project 4 Gerp
 *
 *  Purpose: Trims non alphanumeric characters and converts strings to their
 *  lower case versions.
 *           
 */

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include "stringProcessing.h"

using namespace std;

// stringAlphaNum
// Input: Text from a file
// Description: Eliminates leading and trailing non-alphanumeric ASCII
// chars from a string
// Output: A trimmed text string
void stripNonAlphaNum(string &input) {
    //traverse leading characters
    while (not isAlphaNum(input[0])) {
        input.erase(0, 1);
        
        // if entire string was invalid
        if (input.empty()) {
            input = "";
            return;
        }
    }

    int size = input.length();
    int endChar = size - 1;

    //traverse trailing characters
    while (not isAlphaNum(input[endChar])) {
        input.erase(endChar);
        endChar--;
    }
}

// isAlphaNum
// Input: A character in a text string
// Description: Determines if the character is a number or letter
// Output: True if it is, false if it is not
bool isAlphaNum(char &stringChar) {
    int asciiVal = int(stringChar);

    //check for numbers
    for (int i = 48; i < 58; i++) {
        if (i == asciiVal) {
            return true;
        }
    }

    //check for upper case letters
    for (int i = 65; i < 91; i++) {
        if (i == asciiVal) {
            return true;
        }
    }

    //check for lower case letters
    for (int i = 97; i < 123; i++) {
        if (i == asciiVal) {
            return true;
        }
    }

    return false;
}

// lowerCase
// Input: A reference to the original instance of a word in a file
// Description: Converts each char in a word to its lower case equivalent
// Output: Nothing, but the input string is updated
void lowerCase(string &s) {
    int stringLength = s.length();
    for (int i = 0; i < stringLength; i++) {
        s[i] = tolower(s[i]);
    }
}