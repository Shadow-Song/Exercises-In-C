#include <stdio.h>
int main(void) {
    int a, b, c;
    printf("Input three integers: ");
    scanf("%d %d %d", &a, &b, &c);

    // int sum = ;
    int result = 2 * (a + b + c) + c;
    printf("Twice the sum of integers plus %d is %d !\n", c, result);
    return 0;
}