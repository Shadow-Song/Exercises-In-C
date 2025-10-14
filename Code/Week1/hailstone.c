#include <stdio.h>
#include <stdlib.h>

int* hailstone(int n, int length) {
    int* seq = malloc(length * sizeof(int));
    for (int i = 0; i < length; i++) {
        seq[i] = n;
        if (n == 1) {
            break;
        } else if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
    }
    return seq;
}

int main() {
    int n = 77; // Example starting number   
    int length = 16; // Example length of the sequence
    int* sequence = hailstone(n, length);
    for (int i = 0; i < length; i++) {
        printf("%d ", sequence[i]);
        if (sequence[i] == 1) {
            break;
        }
    }
    printf("\n");
    free(sequence);
    return 0;
}