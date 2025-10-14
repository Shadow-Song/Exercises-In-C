#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int secret, guess, attempts = 0;
    const int max_attempts = 10;

    srand(time(NULL));
    secret = rand() % 1000 + 1;

    printf("I have selected a number between 1 and 1000.\n");
    printf("You have 10 attempts to guess it.\n");

    while (attempts < max_attempts) {
        printf("Attempt %d: Enter your guess: ", attempts + 1);
        if (scanf("%d", &guess) != 1) {
            printf("Invalid input. Please enter an integer.\n");
            while (getchar() != '\n'); // clear input buffer
            continue;
        }
        attempts++;
        if (guess == secret) {
            printf("Congratulations! You guessed the correct number: %d\n", secret);
            return 0;
        } else if (guess < secret) {
            printf("Too low!\n");
        } else {
            printf("Too high!\n");
        }
    }
    printf("Sorry, you've used all your attempts. The number was %d.\n", secret);
    return 0;
}
