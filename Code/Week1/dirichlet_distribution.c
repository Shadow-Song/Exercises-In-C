#include <stdio.h>
#include <stdlib.h>

int first_n_primes(int n) {
    int count_end_by_3 = 0;
    // int* primes = malloc(n * sizeof(int));
    // if (primes == NULL) {
    //     return NULL; // Memory allocation failed
    // }
    int count = 0;
    int candidate = 2; // Start checking for primes from the first prime number

    while (count < n) {
        int is_prime = 1; // Assume candidate is prime
        for (int i = 2; i * i <= candidate; i++) {
            if (candidate % i == 0) {
                is_prime = 0; // Found a divisor, not prime
                break;
            }
        }
        if (is_prime) {
            // primes[count] = candidate;
            if (candidate % 10 == 3) {
                count_end_by_3++;
            }
            count++;
        }
        candidate++;
    }
    return count_end_by_3;
}

int main() {
    int n = 3000; // Number of primes to generate
    int count_end_by_3 = first_n_primes(n);
    printf("Count of prime numbers ending with digit 3 among the first %d primes: %d\n", n, count_end_by_3);
    printf("Proportion: %.2f%%\n", (count_end_by_3 / (float)n) * 100);
    return 0;
}