#include <stdio.h>

int main() {
    int n = 5; // Number of triangle numbers to print
    int triangle = 0;
    for (int i = 0; i <= n; i++) {
        if (i == 0) {
            triangle = 0;
        } else {
            triangle += i;
        }
        printf("%d", triangle);
        if (i < n) {
            printf(", ");
        }
    }
    printf("\n");
    return 0;
}
