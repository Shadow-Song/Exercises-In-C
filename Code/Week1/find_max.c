#include <stdio.h>
#include <float.h>

int main() {
    int count;

    printf("How many numbers do you wish to enter ? ");
    scanf("%d", &count);

    double max = -DBL_MAX;
    double temp;

    printf("Enter %d real numbers: ", count);

    for (int i=0; i<count; i++) {
        scanf("%lf", &temp);
        if (max < temp) {
            max = temp;
        }
    }

    printf("Maximum value: %.2f\n", max);
}