/*
 * BogScorer.cpp
 *
 *  Created on: Apr 12, 2015
 *      Author: cuppar01
 */

#include "BogScorer.h"
#include <iostream>

using namespace std;

BogScorer::BogScorer() {
	correctWords = 0;
	totalScore = 0;
}

//	purpose: read list of valid and unvalid words
void BogScorer::readAnswers() {
	string status;
	string word;

	int i = 0;
	while (cin >> status >> word) {
		ScoreWord newWord;
		newWord.status = status;
		newWord.word = word;
		wordlist.push_back(newWord);
		i++;
	}
}

//	purpose: score answers
void BogScorer::scoreAnswers() {
	for(int i = 0; i < (int)wordlist.size(); i++) {
		// set score to 0 if word is not valid
		if (wordlist[i].status == "NO") {
			wordlist[i].score = 0;
		}

		else {
			int wordLength = (int)wordlist[i].word.length();

			// score word
			if (wordLength == 3) {
				wordlist[i].score = 1;

			}
			else if (wordLength == 4) {
				wordlist[i].score = 1;
			}
			else if (wordLength == 5) {
				wordlist[i].score = 2;
			}
			else if (wordLength == 6) {
				wordlist[i].score = 3;
			}
			else if (wordLength == 7) {
				wordlist[i].score = 5;
			}
			else if (wordLength >= 8) {
				wordlist[i].score = 11;
			}
			correctWords++;
			totalScore = totalScore + wordlist[i].score;
		}
	}
}

//	purpose: print words with score
void BogScorer::printAnswers() {

	for (int i = 0; i < (int)wordlist.size(); i++) {
		cout << wordlist[i].score << " "
			<< wordlist[i].status << " "
			<< wordlist[i].word << endl;
	}

	cout << correctWords << " words " << totalScore << " points" << endl;

}





