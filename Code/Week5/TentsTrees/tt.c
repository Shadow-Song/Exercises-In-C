#include "tentstrees.h"

void test(void) {
    board b;
    // char s[BSIZE*(BSIZE+1)];

    // 0. FAIL : Empty string
    assert(inputboard("", "111111", "222222", &b) ==false);

    // We only compile these lines if BSIZE has been #defined to be 6
    #if BSIZE == 6
        // 1. FAIL : String too long (extra unknown on 5th line)
        assert(inputboard("*    *|    * |      |  *  *|       | **   ","120121", "201112", &b)==false);
        // 2. FAIL : Size not matching BSIZE
        assert(inputboard("*    *|    * |      |  *  *|      | **   ", "12012", "201112", &b)==false);
        // 3. FAIL : Size not digit in counts
        assert(inputboard("*    *|    * |      |  *  *|      | **   ", "120121", "201a12", &b)==false);
        // 4. FAIL : Invalid counts
        assert(inputboard("*    *|    * |      |  *  *|      | **   ", "120127", "201112", &b)==false);
        // 5. FAIL : Total tens per row (6), not same as per column (7)
        assert(inputboard("*    *|    * |      |  *  *|      | **   ", "120121", "201111", &b)==false);
        // 6.1. FAIL : Invalid square ('N')
        assert(inputboard("*    *|    * |  N   |  *  *|      | **   ", "120121", "201112", &b)==false);
        // 6.2. FAIL : Only unknown or tree squares allowed on input, not grass
        assert(inputboard("*    *|    * | ...  |  *  *|      | **   ", "120121", "201112", &b)==false);
        // 7. FAIL : Missing separator
        assert(inputboard("*    *     * |      |  *  *|      | **   ", "120121", "201112", &b)==false);
        // 8. PASS
        assert(inputboard("*    *|    * |      |  *  *|      | **   ", "120121", "201112", &b)==true);
        

    #endif
}

// Input board from string s, with top and side counts
bool inputboard(char* s, char* top, char* side, board* p) {
    // 0. Check for empty string
    if (s[0]=='\0') {
        return false;
    }

    int col_sum = 0;
    int row_sum = 0;

    // 1. Check string length
    size_t expected_length = BSIZE * (BSIZE + 1) - 1; // -1 because no sep at end of last line
    if (strlen(s) != expected_length) {
        return false;
    }

    // 2. Check counts length
    if (strlen(top) != BSIZE || strlen(side) != BSIZE) {
        return false;
    }

    // Load Board Size
    for (int i=0; i<BSIZE; i++) {

        // 3. Check for invalid characters in counts
        if (!isdigit((unsigned char)top[i]) || !isdigit((unsigned char)side[i])) {
            return false;
        }

        p->tents_col[i] = top[i] - '0';
        p->tents_row[i] = side[i] - '0';

        // 4. Check for invalid counts
        if (p->tents_col[i] > BSIZE || p->tents_row[i] > BSIZE) {
            return false;
        }

        col_sum += p->tents_col[i];
        row_sum += p->tents_row[i];
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

bool is_valid_tent_pos(board* p, int r, int c) {
    // Check bounds
    if (r < 0 || r >= BSIZE || c < 0 || c >= BSIZE) {
        return false;
    }

    // Check for occupied squares
    if (p->f[r][c] != unknown) {
        return false;
    }

    // Check adjacent squares for tents (8 directions)
    int directions[8][2] = {
        {-1,0}, {1,0}, 
        {0,-1}, {0,1}, 
        {-1,-1}, {-1,1}, 
        {1,-1}, {1,1}
    };

    for (int i = 0; i < 8; i++) {
        int nr = r + directions[i][0];
        int nc = c + directions[i][1];
            if (nr >= 0 && nr < BSIZE && nc >= 0 && nc < BSIZE) {
                if (p->f[nr][nc] == tent) {
                    return false;
                }
            }
        }

    return true;
}

// Check adjacent squares for trees (4 directions)
bool is_near_tree(board* p, int r, int c) {
    int directions[4][2] = {
        {-1,0}, {1,0}, 
        {0,-1}, {0,1}
    };

    for (int i = 0; i < 4; i++) {
        int nr = r + directions[i][0];
        int nc = c + directions[i][1];
        if (nr >= 0 && nr < BSIZE && nc >= 0 && nc < BSIZE) {
            if (p->f[nr][nc] == tree) {
                return true;
            }
        }
    }

    return false;
}

// Count tents in a given row
int count_tents_in_row(board* p, int r) {
    int count = 0;
    for (int c = 0; c < BSIZE; c++) {
        if (p->f[r][c] == tent) {
            count++;
        }
    }
    return count;
}

// Count tents in a given column
int count_tents_in_col(board* p, int c) {
    int count = 0;
    for (int r = 0; r < BSIZE; r++) {
        if (p->f[r][c] == tent) {
            count++;
        }
    }
    return count;
}



bool solve(board* p) {
    return true;
}



bool board2str(board b, char* s)
{
    return true;
}
