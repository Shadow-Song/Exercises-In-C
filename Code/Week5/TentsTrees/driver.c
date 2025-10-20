#include "tentstrees.h"

int main(void)
{
    test();
    // board b;
    // char s[BSIZE*(BSIZE+1)];

    // // We only compile these lines if BSIZE has been #defined to be 6
    // #if BSIZE == 6
    //     // Solvable
    //     assert(inputboard("*    *|    * |      |  *  *|      | **   ", "120121", "201112", &b)==true);
    //     assert(solve(&b)==true);
    //     assert(board2str(b,s));
    //     assert(strcmp("*+..+*|....*.|....+.|.+*..*|.....+|+**+..", s)==0);


    //     // Solvable
    //     assert(inputboard(" *    |   *  |     *|      |**    |   ** ", "121111", "111103", &b)==true);
    //     assert(solve(&b)==true);
    //     assert(board2str(b,s));
    //     assert(strcmp(".*.+..|.+.*..|....+*|.+....|**....|+.+**+", s)==0);

    //     // Solvable
    //     assert(inputboard("   *  |  **  | *    |      |*    *| *    ", "121111", "111202", &b)==true);
    //     assert(solve(&b)==true);
    //     assert(board2str(b,s));
    //     assert(strcmp("...*+.|.+**..|.*.+..|.+...+|*....*|+*+...", s)==0);

    //     // NOT Solvable
    //     assert(inputboard("    * |  *   |   *  | *   *|  *   |*     ", "112012", "111121", &b)==true);
    //     assert(solve(&b)==false);
    // #endif

    // #if BSIZE == 4
    //     assert(inputboard("*  *|    |*   |   *", "1111", "1102", &b)==true);
    //     assert(solve(&b)==true);
    //     assert(board2str(b,s));
    //     assert(strcmp("*+.*|...+|*...|+.+*", s)==0);
    // #endif
    return EXIT_SUCCESS;
}
