#include <stdio.h>

int is_triangle(int a, int b, int c) {
    // Check for positive lengths
    if (a <= 0 || b <= 0 || c <= 0) {
        return -1; // Negative or zero side
    }
    // Triangle inequality
    if (a + b <= c || a + c <= b || b + c <= a) {
        return 0; // Impossible triangle
    }
    return 1; // Valid triangle
}

int main() {
    int a, b, c;
    printf("Enter triples of side lengths (enter -999 as the first value to quit):\n");
    while (1) {
        printf("Enter three side lengths: ");
        if (scanf("%d %d %d", &a, &b, &c) != 3) {
            printf("Invalid input. Please enter three integers.\n");
            while (getchar() != '\n'); // clear input buffer
            continue;
        }
        if (a == -999) {
            printf("Terminating program.\n");
            break;
        }
        int result = is_triangle(a, b, c);
        if (result == -1) {
            printf("Error: All sides must be positive integers.\n");
        } else if (result == 0) {
            printf("Error: These sides do not form a valid triangle.\n");
        } else {
            printf("Valid triangle: %d %d %d\n", a, b, c);
        }
    }
    return 0;
}
