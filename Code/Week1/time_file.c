#include <stdio.h>
#include <stdlib.h>

int time_difference(int h1, int m1, int h2, int m2) {
    if (h1 < 0 || h1 > 23 || m1 < 0 || m1 > 59 || h2 < 0 || h2 > 23 || m2 < 0 || m2 > 59) {
        return -1; // Invalid time
    }
    int total_minutes1 = h1 * 60 + m1;
    int total_minutes2 = h2 * 60 + m2;
    int diff = total_minutes2 - total_minutes1;
    if (diff < 0) {
        diff += 24 * 60; // Adjust for next day
    }
    return diff;
}

int main() {
    int h1, m1, h2, m2;
    printf("Enter two times in 24-hour format (HH:MM HH:MM): ");
    if (scanf("%d:%d %d:%d", &h1, &m1, &h2, &m2) != 4) {
        printf("Invalid input. Please enter four integers.\n");
        return 1;
    }
    int diff = time_difference(h1, m1, h2, m2);
    if (diff == -1) {
        printf("Error: Invalid time entered.\n");
    } else {
        int hours = diff / 60;
        int minutes = diff % 60;
        printf("Time difference: %d:%d\n", hours, minutes);
    }
    return 0;
}