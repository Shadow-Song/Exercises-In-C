#include <stdio.h>
#include <stdlib.h>

int* first_n_primes(int n) {
    int* primes = malloc(n * sizeof(int));
    if (primes == NULL) {
        return NULL; // Memory allocation failed
    }
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
            primes[count] = candidate;
            count++;
        }
        candidate++;
    }
    return primes;
}

int main() {
    int n = 3000; // Number of primes to generate
    int* primes = first_n_primes(n);
    if (primes == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    printf("First %d prime numbers:\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", primes[i]);
    }
    printf("\n");
    free(primes);
    return 0;
}