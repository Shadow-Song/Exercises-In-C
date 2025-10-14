#include <stdio.h>
#include <stdlib.h>

int main() {
    int median = RAND_MAX / 2;
    int minus_cnt = 0;
    int plus_cut = 0;
    for (int i=0; i< 500; i++) {
        int temp = rand();
        // printf("Temp: %d ", temp);
        if (temp < median) {
            minus_cnt++;
        } else {
            plus_cut++;
        }
        printf("Minus: %d, Plus: %d\n", minus_cnt, plus_cut);
    }
    return 0;
}