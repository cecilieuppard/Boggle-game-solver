/*
 * BogValidator.h
 *
 *  Created on: Apr 10, 2015
 *      Author: cuppar01
 */

#ifndef BOGVALIDATOR_H
#define BOGVALIDATOR_H

#include "Dictionary.h"
#include "BogWordList.h"

class BogValidator
{
public:
	BogValidator(); // constructor
	~BogValidator(); // destructor
	bool readDict(); // read in a dictionary
	bool readBoard(); // read in a board
	bool solve();	// search board for words in dict
	bool isValid(std::string s); // validates one word
	void checkWords(); // validates cin. The end of input will
			   // simply return NULL to cin.
private:
	Dictionary dict; 		// must use a Dictionary
	vector <string> solvedWords;	// list of solved words from board
	vector <string> validWords;	// list of valid input words
	vector<vector<char> > bogBoard;	// the boggle board
	int row, col;			// number of rows and cols in board
	bool findWord(int row, int col, string prefix, BogWord word);
};

#endif

