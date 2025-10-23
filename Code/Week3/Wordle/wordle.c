/* 
 * wordle.c
 * 
 * Implementation of functions to count "greens" and "yellows" in a Wordle guess.
 * Greens are letters that are correct and in the correct position.
 * Yellows are letters that are correct but in the wrong position.
 *
 * Modified by Cenarius Lu <ig25518@bristol.ac.uk>.
 */

#include "wordle.h"

int num_greens(char answer[], char guess[]){
	int greens = 0;
	for (int i = 0; i < 5; i++){
		// Check if the letters match in the same position (case-insensitive)
		if (tolower(guess[i]) == tolower(answer[i])) greens++;
	}
	return greens;
}

int num_yellows(char answer[], char guess[]){
	// Duplicate the arrays to avoid modifying the originals
	answer = strdup(answer);
	guess = strdup(guess);
	int yellows = 0;
	// bool matched[10] = {false};

	for (int i = 0; i < 5; i++){
		// Check if the letters match in the same position (case-insensitive)
		if (tolower(guess[i]) == tolower(answer[i])) {
			// Mark this position as guessed
			guess[i] = '*'; // Invalidate this position in guess
			answer[i] = '*'; // Invalidate this position in answer
		}
	}

	for (int i = 0; i < 5; i++){
		if (answer[i] == '*') continue; // Skip already guessed positions
		for (int j = 0; j < 5; j++){
			if (guess[j] != '*' && tolower(answer[i]) == tolower(guess[j])) {
				yellows++;
				guess[j] = '*'; // Invalidate this position in guess
				answer[i] = '*'; // Invalidate this position in answer
				break; // Move to the next letter in guess
			}
		}
	}

	return yellows;
}

void test(void){
	// Basic tests
	char word1[6] = "HELLO";
	char word2[6] = "WORLD";
	// 'L' is green, 'O' is yellow
	assert(num_greens(word1, word2) == 1);
	assert(num_yellows(word1, word2) == 1);

	// Reverse should give same result
	strcpy(word1, "APPLE");
	strcpy(word2, "ALLEY");
	// 'A' is green, 'L' and 'E' are yellow
	assert(num_greens(word1, word2) == 1);
	assert(num_yellows(word1, word2) == 2);
	// Should give same result if answer and guess swapped
	assert(num_greens(word2, word1) == 1);
	assert(num_yellows(word2, word1) == 2);

	// Case insensitivity test
	strcpy(word1, "Alley");
	strcpy(word2, "APPLE");
	assert(num_greens(word1, word2) == 1);
	assert(num_yellows(word1, word2) == 2);

	// No matches
	strcpy(word1, "ABCDE");
	strcpy(word2, "FGHIJ");
	assert(num_greens(word1, word2) == 0);
	assert(num_yellows(word1, word2) == 0);

	// All letters match but in wrong positions
	strcpy(word1, "ABCDE");
	strcpy(word2, "EABCD");
	assert(num_greens(word1, word2) == 0);
	assert(num_yellows(word1, word2) == 5);

	// All letters match in correct positions
	strcpy(word1, "ABCDE");
	strcpy(word2, "ABCDE");
	assert(num_greens(word1, word2) == 5);
	assert(num_yellows(word1, word2) == 0);

	// Single letter words
	strcpy(word1, "IIIII");
	strcpy(word2, "IIIII");
	assert(num_greens(word1, word2) == 5);
	assert(num_yellows(word1, word2) == 0);

	// Duplicated letters
	strcpy(word1, "AABBB");
	strcpy(word2, "ABABA");
	assert(num_greens(word1, word2) == 2);
	assert(num_yellows(word1, word2) == 2);
	assert(num_greens(word2, word1) == 2);
	assert(num_yellows(word2, word1) == 2);
}
