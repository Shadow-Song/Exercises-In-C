#include "tentstrees.h"

void test(void)
{
    board b;
    // char s[BSIZE*(BSIZE+1)];

    // 0. FAIL : Empty string
    assert(inputboard("", "111111", "222222", &b) ==false);

    // We only compile these lines if BSIZE has been #defined to be 6
    #if BSIZE == 6
        // 1. FAIL : String too long (extra unknown on 5th line)
        assert(inputboard("*    *|    * |      |  *  *|       | **   ","120121", "201112", &b)==false);
        // 2. FAIL : Size not matching BSIZE
        assert(inputboard("*   *|    * |      |  *  *|      | **   ", "12012", "201112", &b)==false);
        // 3. FAIL : Invalid counts
        assert(inputboard("*   *|    * |      |  *  *|      | **   ", "120127", "201112", &b)==false);
        // 4. FAIL : Size not digit in counts
        assert(inputboard("*   *|    * |      |  *  *|      | **   ", "120127", "201A12", &b)==false);
        // 5. FAIL : Total tens per row (6), not same as per column (7)
        assert(inputboard("*    *|    * |      |  *  *|      | **   ", "120121", "201111", &b)==false);
        // 6.1. FAIL : Invalid square ('N')
        assert(inputboard("*    *|    * |  N   |  *  *|      | **   ", "120121", "201112", &b)==false);
        // 6.2. FAIL : Only unknown or tree squares allowed on input, not grass
        assert(inputboard("*    *|    * | ...  |  *  *|      | **   ", "120121", "201112", &b)==false);
        

    #endif
}

bool inputboard(char* s, char* top, char* side, board* p)
{
    // 0. Check for empty string
    if (s[0]=='\0') {
        return false;
    }

    int col_sum = 0;
    int row_sum = 0;

    // 1. Check string length
    size_t expected_length = BSIZE * (BSIZE + 1) - 1; // -1 because no sep at end of last line
    if (strlen(s) != expected_length) return false;

    // 2. Check counts length
    if (strlen(top) != BSIZE || strlen(side) != BSIZE) return false;

    // Load Board Size
    for (int i=0; i<BSIZE; i++) {

        // 3. Check for invalid counts
        if (p->tents_col[i] > BSIZE || p->tents_row[i] > BSIZE) {
            return false;
        }

        // 4. Check for invalid characters in counts
        if (!isdigit((unsigned char)top[i]) || !isdigit((unsigned char)side[i])) {
            return false;
        }
        
        col_sum += top[i] - '0';
        row_sum += side[i] - '0';

        p->tents_col[i] = top[i] - '0';
        p->tents_row[i] = side[i] - '0';
    }

    // 5. Check string sum for columns and rows
    if (col_sum != row_sum) {
        return false;
    }

    // Load Board Squares
    for (int r=0; r<BSIZE; r++) {
        for (int c=0; c<BSIZE; c++) {
            char ch = s[r*(BSIZE+1)+c];
            // 6. Check for invalid characters
            if (ch != unknown && ch != tree) {
                return false;
            }
            p->f[r][c] = ch;
        }

        // 7. Check for separator
        if (s[(r+1)*(BSIZE+1)-1] != sep && r < BSIZE-1) {
            return false;
        }
    }

    return true;
}

// bool solve(board* p)
// {
//     return false;
// }

// bool board2str(board b, char* s)
// {
//     return true;
// }
