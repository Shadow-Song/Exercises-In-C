#include <stdio.h>
#include <stdlib.h>

int hailstone_return_1(int n) {
    int count = 0;
    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        count++;
    }

    return count;
}

int hailstone_return_max(int n) {
    int max = n;
    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        if (n > max) {
            max = n;
        }
    }

    return max;
}

int main() {
    int longest_steps = 0;
    int longest_num = 1;
    int max_value = 0;
    int largest_num = 1;
    
    for (int i = 1; i < 10000000; i++) {
        int steps = hailstone_return_1(i);
        if (steps > longest_steps) {
            longest_steps = steps;
            longest_num = i;
        }
        int current_max = hailstone_return_max(i);
        if (current_max > max_value) {
            max_value = current_max;
            largest_num = i;
        }
    }
    printf("Initial number under 10,000,000 with the longest hailstone sequence: %d\n", longest_num);
    printf("Length of sequence (steps to reach 1): %d\n", longest_steps);
    printf("Maximum value reached in any sequence: %d\n", max_value);
    printf("Starting number that produces the maximum value: %d\n", largest_num);

    return 0;
}