#include <stdio.h>

int main() {
    int count;

    printf("How many numbers do you wish to enter ? ");
    scanf("%d", &count);

    int max = -2147483648;  // Minimum value for int
    int temp;

    printf("Enter %d integers: ", count);

    for (int i=0; i<count; i++) {
        scanf("%d", &temp);
        if (temp % 2 != 0) {
            printf("Odd number: %d.\n", temp);
            if (max < temp) {
                max = temp;
            }
        } else {
            printf("Even number: %d, ignored.\n", temp);
        }

    }

    printf("Maximum value: %d\n", max);
}