#include <stdio.h>
#define A 7
#define C 5
#define M 11
#define LOOPS 10

int main() {
    int seed = 0;
    /* Linear Congruential Generator */
    for(int i=0; i<LOOPS; i++){
        seed = (A*seed + C) % M;
        /* Seed now contains your new random number */
        printf("Random number %d: %d\n", i+1, seed);
    }
    return 0;
}