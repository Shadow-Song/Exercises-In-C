#include <stdio.h>
#include <math.h>

double demonstrate(double x) {
    double result = sin(x)*sin(x) + cos(x)*cos(x);
    return result;
}

int main() {
    double x;
    printf("Enter a real number: ");
    scanf("%lf", &x);
    printf("Result: %f\n", demonstrate(x));
    return 0;
}