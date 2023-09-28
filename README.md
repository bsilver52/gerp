# gerp

/**********************************************************
* Project 4: Gerp
* Benjamin Silver and Joel MacVicar
* April 28, 2023
* CS 15 Data Structures
* README
**********************************************************

A. Title and Authors:
Title: Project 3 Gerp
Author: Benjamin Silver and Joel MacVicar

B. Purpose
The purpose of this program is to provide a program for the client that
indexes a directory and searches for words within its files

C. Files
1. main.cpp: This is the driver file for the gerp program
2. gerp.cpp: This file allows the client to locate instances of word for files
in a root directory
3. gerp.h: This file searches and indexes files for the client using a hash
 table
4. wordHash.cpp: This file hashes the words in a file in order for the client
 toperform word queries
5. wordHash.h: This file stores the hash table necessary for indexing query
information
6. DirNode.h: Contains the file/directory nodes that compose a file system tree
7. FSTree.h: Contains an n-ary tree to represent a file system
8. stringProcessing.cpp: Trims non alphanumeric characters and converts
strings to their lower case versions.
9. stringProcessing.h: Parses strings for the wordHash and gerp classes
10. unit_tests.h: Tests the functionality of the stringProcessing functions 
and hash table creation for single files/entire directories
11. Makefile: Automates the compilation and linking process for gerp

D. Compiling and Running:
     - Compile using
            make gerp
     - Run executable with
            ./gerp inputDirectory outputFile
*Note that this program will only run effectively for valid directories. Per 
TA instructions, our program need not handle cases where the file index cannot
build

E. Architectural Overview
Our gerp implementation contains a driver file. This calls thee public "run"
function in the gerp class if command line arguments are specified correctly.
The gerp class first builds a file index by creating an n-nary tree from the
files in the client-specified root directory using the FSTree class. The tree
is built using DirNode objects, which represent the directories (internal
nodes) and files (leafs) contained in a root directory. Gerp then initializes
a wordHash object. This class contains the hash table used to quickly output
word occurences. The hash table is an array list (see next section) of
structs. Each struct is a bucket that stores the following information 1.
whether the bucket is filled 2. the word at that index 3. a vector of all the
files occurences 4. a vector containing a vector for each file, which has all
the line number occurences for a given file 5. A vector all the permutations
of a word that is present within the root directory. Finally, the hash table
also contains a vector of pairs, containing the file name and lines a word
occurs on. While this information may appear redundant, this vector was used
to prevent lines from printing multiple times when multiple instances of a
word occurs on a single line during the insensitive search. Both the gerp and
wordHash classes use stringProcessing functions. The trim function is used to
trim leading/trailing non-alpha numeric characters from client queries and file
text.

F. Data structures 

Hash Table: A hash tables provides the O(1) lookup and indexing of an array,
            but instead of using numbers, users input a string (a key 
            basically). Hash tables utilize a hash fucntion to convert
            the desired key (usually a string) into a unique index, which
            can be manipulated to input the corresponding value into bucket.
            If two keys map to the same bucket, the "collision" must be 
            handled using either chaining (making the bucket a list of 
            buckets) or open addressing (finding another empty spot in the
            table to insert). Hash tables can be implemented using vectors 
            givne their similarity to arrays. 
                        
Hash Table Algos: As alluded to above, there are several essential algos
                  needed to make a hash table work. They are: hashing the key,
                  adjusting the hash to the table size, handling 
                  collisions, and expanding when loadFactor is hit (0.7). 
                  
Our Hash Table: We implemented our hash table as a vector of structs 
                (our buckets). In each struct we included a bool filled
                (needed for how we handled collisions), the string that 
                is the key, a vector of files in which the key occurs,
                a 2d vector of lines the word occurs on in each vector,
                and a vector containing all permutations of the word.
                
                A few important things to note about our hashtable:
                 - While our function only cares about the contents of the
                   line, we chose not to store this info to save space. 
                 - The file at index j of the file vector corresponds to the
                   line numbers at index [j][:] of the 2d line num vector.
                 - the allPerm vector is ONLY populated at the fully lowercase
                   version of each word, and is empty in all other buckets. 
                  
Our Hash Table Algos: We used the c++ hash fucntion to generate our distinct 
                     hash #. Then, we moded by our table size to get an index
                     in our hash table (aka vector of buckets). If an item is
                     already in that slot, we handle the collision using linar
                     probing. We made sure that if we hit the end of the table
                     we looped back to index 0. When our table reached a load
                     factor of 0.7, we stored the contents of the table in a 
                     temp vector, doubled the hash table size, then rehashed 
                     the info in the old table to populate the new one. 
