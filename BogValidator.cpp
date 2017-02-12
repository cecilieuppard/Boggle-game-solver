/*
 * BogValidator.cpp
 *
 *  Created on: Apr 11, 2015
 *      Author: cuppar01
 */

#include "BogValidator.h"
#include "BogWordList.h"
#include "Dictionary.h"
#include <ctype.h>
#include <vector>
#include <stdlib.h>

using namespace std;

BogValidator::BogValidator() {
	row = 0;
	col = 0;
}

BogValidator::~BogValidator() {
}

//	purpose: read in dictionary ad convert words to upper case
bool BogValidator::readDict() {
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

//	purpose: read in dimensions and letters of boggle board
bool BogValidator::readBoard() {

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

			if (cin.eof()) {
				exit(-1);
			}
		}
		bogBoard.push_back(boardRow);
	}

	//solve board to create list of possibly valid words
	solve();

	return true;
}

// 	purpose: solve board and store in wordlist to be compared with input
bool BogValidator::solve() {

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			// pass in BogWord to keep track of letter coordinates
			BogWord word;
			findWord(i, j, "", word);
		}
	}
	return true;
}

//	purpose: helper function to search for words in board
bool BogValidator::findWord(int r, int c, string prefix, BogWord word) {

	if (((r < 0) or (r >= row)) or ((c < 0) or (c >= col))) {
		return false;
	}

	// return false if letter has been used before
	for (int i = 0; i < (int)word.size(); i++) {
		if ((r == word[i].row) and (c == word[i].col)) {
			return false;
		}
	}

	// update the string prefix, if Q - add U
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

	// if word is longer than two letters and string is word in dictionary
	if (((int)word.size() > 2) and (dict.isWord(prefix))) {
		solvedWords.push_back(prefix);
	}

	// if prefix is not a prefix in dictionary return false
	if (!dict.isPrefix(prefix)) {
		return false;
	}

	// if prefix is in dictionary but is not a word yet, recurse
	for (int i = r - 1; i <= r + 1; i++) {
		for (int j = c -1; j <= c + 1; j++) {
			if (! ((i == r) and (j == c))) {
				findWord(i,j, prefix, word);
			}
		}
	}
	return true;
}

//	purpose: check if one word is valid
bool BogValidator::isValid(std::string s) {
	if (!dict.isWord(s)) {
		return false;
	}

	// return false if word has been validated before/is duplicate
	for (int i = 0; i < (int)validWords.size(); i++) {
		if (validWords[i] == s) {
			return false;
		}
	}

	// compare string with solved words, return true if match
	for (int i = 0; i < (int)solvedWords.size(); i++) {
		if (solvedWords[i] == s) {
			validWords.push_back(s);
			return true;
		}
	}

	return false;
}

//	purpose: read in, validate and print report of words
void BogValidator::checkWords() {
	string word;

	while (cin >> word) {
		if (isValid(word)) {
			cout << "OK" << " " << word << endl;
		}
		else {
			cout << "NO" << " "<< word << endl;
		}
	}
}









