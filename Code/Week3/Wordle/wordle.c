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
	char word1[6] = "HELLO";
	char word2[6] = "WORLD";

	// 'L' is green, 'O' is yellow
	assert(num_greens(word1, word2) == 1);
	assert(num_yellows(word1, word2) == 1);

	strcpy(word1, "APPLE");
	strcpy(word2, "ALLEY");

	// 'A' is green, 'L' and 'E' are yellow
	assert(num_greens(word1, word2) == 1);
	assert(num_yellows(word1, word2) == 2);

	// Should give same result if answer and guess swapped
	assert(num_greens(word2, word1) == 1);
	assert(num_yellows(word2, word1) == 2);
}
