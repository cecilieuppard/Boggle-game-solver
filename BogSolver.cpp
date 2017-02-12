/*
 * BogSolver.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: cuppar01
 */

#include "BogSolver.h"
#include "BogWordList.h"
#include "Dictionary.h"
#include <ctype.h>
#include <vector>
#include <stdlib.h>

using namespace std;

// constructor
BogSolver::BogSolver() {
	row = 0;
	col = 0;
}
// destructor
BogSolver::~BogSolver() {
}

//	purpose: read in dictionary ad convert words to upper case
bool BogSolver::readDict() {
	string word;
	do {
		if (!(cin >> word)) {
			return false;
		}
		if (word != ".") {
			for (int i = 0; i < (int)word.size(); i++) {
				word[i] = toupper(word[i]);
			}
			if (!dict.insert(word)) {
				return false;
			}
		}
	} while (word != "."); // stop if word is "."

	return true;
}

bool BogSolver::readBoard() {

	if (!(cin >> row >> col)) {
		return false;
	}

	for (int i = 0; i < row; i++) {
		vector<char> boardRow;
		for (int j = 0; j < col; j++) {
			char letter;
			cin >> letter;
			letter = toupper(letter);
			boardRow.push_back(letter);
			// return false if at end of file
			if (cin.eof()) {
				exit (-1);
			}
		}
		// push row onto board
		bogBoard.push_back(boardRow);
	}
	return true;
}

bool BogSolver::solve() {

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			// pass in BogWord to keep track of letter coordinates
			BogWord word;
			findWord(i, j, "", word);
		}
	}
	return true;
}

bool BogSolver::findWord(int r, int c, string prefix, BogWord word) {

	// return false if out of bounds
	if (((r < 0) or (r >= row)) or ((c < 0) or (c >= col))) {
		return false;
	}

	// return false if letter has been used before
	for (int i = 0; i < (int)word.size(); i++) {
		if ((r == word[i].row) and (c == word[i].col)) {
			return false;
		}
	}

	// update the string prefix, if Qu - add U
	if (bogBoard[r][c] == 'Q') {
		prefix = prefix + bogBoard[r][c] + 'U';
	}
	else {
		prefix = prefix + bogBoard[r][c];
	}

	// update the BogWord
	BogLett newLetter;
	newLetter.c = bogBoard[r][c];
	newLetter.row = r;
	newLetter.col = c;
	word.push_back(newLetter);

	if ((bogWordLength(word) > 2) and (dict.isWord(prefix))) {
		wordlist.push_back(word);

		if(!(checkDuplicate(prefix))) {
			withoutduplicates.push_back(word);
		}
	}

	if (!dict.isPrefix(prefix)) {
		return false;
	}

	// if prefix is prefix in dictionary but not currently a word, recurse
	for (int i = r - 1; i <= r + 1; i++) {
		for (int j = c -1; j <= c + 1; j++) {
			if (! ((i == r) and (j == c))) {
				findWord(i,j, prefix, word);
			}
		}
	}
	return true;
}

//	purpose: return number of words found in board
int BogSolver::numWords() {
	int num_words = 0;

	for (int i = 0; i < (int)withoutduplicates.size(); i++) {
		num_words++;
	}

	return num_words;
}

//	purpose: return number of words of len size found in board
int BogSolver::numWords(int len) {
	int num_words = 0;

	for (int i = 0; i < (int)withoutduplicates.size(); i++) {
		if ((int)withoutduplicates[i].size() == len) {
			num_words++;
		}
	}

	return num_words;
}

//	purpose: return the list of all words found in board
BogWordList* BogSolver::getWords() {
	// caller is responsible for deleting
	BogWordList* list = new BogWordList;

	for (int i = 0 ; i < (int)withoutduplicates.size(); i++) {
		list -> push_back(withoutduplicates[i]);
	}

	return list;
}

BogWordList* BogSolver::getWords(int len) {
	// caller is responsible for deleting
	BogWordList* list = new BogWordList;

	for (int i = 0 ; i < (int)withoutduplicates.size(); i++) {
		if((int)withoutduplicates[i].size() == len) {
			list -> push_back(withoutduplicates[i]);
		}
	}

	return list;
}

//	purpose: print all words in HBF format
void BogSolver::printWords() {

	for (int i = 0; i < (int)wordlist.size(); i++) {
		cout << "<";
		for (int j = 0; j < (int)wordlist[i].size(); j++) {
			if (wordlist[i][j].c == 'Q') {
				cout << " "
					<< wordlist[i][j].c << "U" << " "
					<< wordlist[i][j].row << " "
					<< wordlist[i][j].col;
			}
			else {
				cout << " "
					<< wordlist[i][j].c << " "
					<< wordlist[i][j].row << " "
					<< wordlist[i][j].col;
			}
		}
		cout << " >" << endl;
	}
	cout << "< >" << endl;
}

//	purpose: print all words of len length in HBF format
void BogSolver::printWords(int len) {
	for (int i = 0; i < (int)wordlist.size(); i++) {
		cout << "<";
		if((int)wordlist[i].size() == len) {
			for (int j = 0; j < (int)wordlist[i].size(); j++) {
				if (wordlist[i][j].c == 'Q') {
					cout << " "
					<< wordlist[i][j].c << "U" << " "
					<< wordlist[i][j].row << " "
					<< wordlist[i][j].col;
				}
				else {
					cout << " "
					<< wordlist[i][j].c << " "
					<< wordlist[i][j].row << " "
					<< wordlist[i][j].col;
				}
			}
			cout << " >" << endl;
		}
	}
	cout << "< >" << endl;
}

//	purpose: print all words, without coordinates
void BogSolver::listWords() {
	for (int i = 0; i < (int)withoutduplicates.size(); i++) {
		for (int j = 0; j < (int)withoutduplicates[i].size(); j++) {
			if (withoutduplicates[i][j].c == 'Q') {
				cout << withoutduplicates[i][j].c << "U";
			}
			else {
				cout << withoutduplicates[i][j].c;
			}
		}
		cout << endl;
	}
}

//	purpose: print all words of len length, without coordinates
void BogSolver::listWords(int len) {
	for (int i = 0; i < (int)withoutduplicates.size(); i++) {
		if((int)withoutduplicates[i].size() == len) {
			for (int j = 0; j < (int)withoutduplicates[i].size();
				j++) {
				if (withoutduplicates[i][j].c == 'Q') {
					cout << withoutduplicates[i][j].c
					<< "U";
				}
				else {
					cout << withoutduplicates[i][j].c;
				}
			}
			cout << endl;
		}
	}
}

//	purpose: check if word has already been found in board
bool BogSolver::checkDuplicate(string s) {
	for (int i = 0; i < (int)withoutduplicates.size(); i++) {
		string temp = "";
		for(int j = 0; j < (int)withoutduplicates[i].size(); j++) {
			// break if at end of string
			if (j == (int)s.length()) {
				break;
			}
			if (s[j] == withoutduplicates[i][j].c) {
				temp += s[j];
			}
			else {
				break;
			}

		}
		if (temp == s) {
			return true;
		}
	}
	return false;
}

//	purpose: return the length of the word - in case word has Q
int BogSolver::bogWordLength(BogWord word) {

	for (int i = 0; i < (int)word.size(); i++) {
		if (word[i].c == 'Q') {
			return ((int)word.size() + 1);
		}
	}

	return ((int)word.size());
}









