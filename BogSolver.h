/*
 * BogSolver.h
 *
 *  Created on: Apr 10, 2015
 *      Author: cuppar01
 */

#ifndef BOGSOLVER_H
#define BOGSOLVER_H

#include "BogWordList.h"
#include "Dictionary.h"

class BogSolver
{
    public:
	BogSolver();
	~BogSolver();
	bool readDict();
	bool readBoard();
	bool solve();			// search board for words in dict
	int  numWords();		// returns number of words found
	int  numWords(int len);		// number of words of length len
	BogWordList* getWords();	// returns all words found
	BogWordList* getWords(int len);	// returns words of len len
	void printWords();		// print all words in HBF
	void printWords(int len);	// print len-length words in HBF
	void listWords();		// print just the text, no coords
	void listWords(int len);	// just the text, no coords

   private:
	Dictionary dict;		// must use a Dictionary
	BogWordList wordlist;		// list for storing words
	BogWordList withoutduplicates;	// list of all non-duplicate words
	vector<vector<char> > bogBoard;	// the boggle board
	int row, col;			// number of rows and cols in board
	bool findWord(int row, int col, string prefix, BogWord word);
	bool checkDuplicate(string word); // checks if a word is duplicate
	int bogWordLength(BogWord word); // checks if Bogword has Q
};
#endif
