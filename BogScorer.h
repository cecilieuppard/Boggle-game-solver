/*
 * BogScorer.h
 *
 *  Created on: Apr 12, 2015
 *      Author: cuppar01
 */

#ifndef BOGSCORER_H
#define BOGSCORER_H

#include <string>
#include <vector>
#include <iostream>

struct ScoreWord {
	std::string status;
	std::string word;
	int score;
};

class BogScorer {
public:
	BogScorer();
	void readAnswers();
	void scoreAnswers();
	void printAnswers();
private:
	int correctWords;		// correct words
	int totalScore;			// total score
	std::vector <ScoreWord> wordlist;// list of words with score
};

#endif
