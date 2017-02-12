# ReadMe for COMP 15 HW6
# Boggle Assignment
# Cecilie Uppard


Purpose:
To solve a Boggle board using three different programs, BogSolver, 
BogValidatior and BogScorer. Collectively they read in a dictionary, a board,
solves the board by finding all possible words, validates the input from
the client and scores their input. The programs work independently, but solves
a Boggle board together by BogValidator taking in BogSolver's output and
BogScorer taking in BogValidator's output.

Files:
BogSolver.h - declaration of the class BogSolver.

BogSolver.cpp - implementation of the class BogSolver. The program reads in 
		a dictionary, a boggle board and its dimensions and finds
		all words that can be found in the board. It outputs these
		as a list.
		
BogValidator.h - declaration of the class BogValidator.

BogValidator.cpp - implementation of the class BogValidator. The program
		   reads in a dictionary and a boggle board, if working 
		   together with BogSolver, the same dictionary and board as
		   BogSolver. It then solves the board and stores all the words
		   found in a list. It then compares input from the client
		   with these words, validating whether the words the client
		   inputs is in the board and dictionary, or not. It outputs
		   all the words inputed preceded by a "OK" for valid words
		   and a "NO" for invalid words.

BogScorer.h - declaration of the class BogScorer.

BogScorer.cpp - implementation of the class BogScorer. The program reads in 
		a list of words preceded by either "OK" or "NO". If a word is
		preceded by "OK" it counts the number of letters and gives
		the word a score that is decided by the rules of Hasbro's 
		Boggle game. If a word is preceded by "NO" it gives the word
		a score of 0. The program then outputs all the words with
		their validity status and score, followed by a number of 
		total valid words and total score.
		

Compile:
Using included makefile

Data structures:
The data structures used in these programs are mostly vectors, holding either
defined structs or std::strings. The board is represented by a 2D vector and
the dictionary, which I did not write, is stored in a trie.

Algorithm:
For solving the board recursion is used for checking the letters surrounding
a specific letter. The algorithms otherwise mostly consist of checking for 
different cases using conditionals and depend on the program. 


