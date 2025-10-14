#include <stdio.h>

int main() {
    while (1) {
        printf("How much money would you like? ");
        int amount;
        scanf("%d", &amount);

        int twenties = amount / 20;
        if (amount % 20 != 0) {
            printf("I can give you %d or %d, try again.\n", twenties * 20, (twenties + 1) * 20);
        } else {
            printf("OK, dispensing ...\n");
            break;
        }
    }

    return 0;
}