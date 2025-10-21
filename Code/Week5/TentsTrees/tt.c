/*
 * Tents and Trees puzzle solver
 * 
 * by Cenarius Lu <ig25518@bristol.ac.uk>
 */

#include "tentstrees.h"


// Input board from string s, with top and side counts
bool inputboard(char* s, char* top, char* side, board* p) {
    // 0. Check for NULL pointers
    if (s == NULL || top == NULL || side == NULL || p == NULL) {
        return false;
    }

    // 1. Check for empty string
    if (s[0]=='\0') {
        return false;
    }

    int col_sum = 0;
    int row_sum = 0;

    // 2. Check string length
    size_t expected_length = BSIZE * (BSIZE + 1) - 1; // -1 because no sep at end of last line
    if (strlen(s) != expected_length) {
        return false;
    }

    // 3. Check counts length
    if (strlen(top) != BSIZE || strlen(side) != BSIZE) {
        return false;
    }

    // Load Board Size
    for (int i=0; i<BSIZE; i++) {

        // 4. Check for invalid characters in counts
        if (!isdigit((unsigned char)top[i]) || !isdigit((unsigned char)side[i])) {
            return false;
        }

        p->tents_col[i] = top[i] - '0';
        p->tents_row[i] = side[i] - '0';

        // 5. Check for invalid counts
        if (p->tents_col[i] > BSIZE || p->tents_row[i] > BSIZE) {
            return false;
        }

        col_sum += p->tents_col[i];
        row_sum += p->tents_row[i];
    }

    // 6. Check string sum for columns and rows
    if (col_sum != row_sum) {
        return false;
    }

    // Load Board Squares
    for (int r=0; r<BSIZE; r++) {
        for (int c=0; c<BSIZE; c++) {
            char ch = s[r*(BSIZE+1)+c];
            // 7. Check for invalid characters
            if (ch != unknown && ch != tree) {
                return false;
            }
            p->f[r][c] = ch;
        }

        // 8. Check for separator
        if (s[(r+1)*(BSIZE+1)-1] != sep && r < BSIZE-1) {
            return false;
        }
    }

    return true;
}

// Helper function: Count tents in a row
int count_tents_in_row(board* p, int row) {
    int count = 0;
    for (int c = 0; c < BSIZE; c++) {
        if (p->f[row][c] == tent) {
            count++;
        }
    }
    return count;
}

// Helper function: Count tents in a column
int count_tents_in_col(board* p, int col) {
    int count = 0;
    for (int r = 0; r < BSIZE; r++) {
        if (p->f[r][col] == tent) {
            count++;
        }
    }
    return count;
}

// Helper function: Count unknowns in a row
int count_unknowns_in_row(board* p, int row) {
    int count = 0;
    for (int c = 0; c < BSIZE; c++) {
        if (p->f[row][c] == unknown) {
            count++;
        }
    }
    return count;
}

// Helper function: Count unknowns in a column
int count_unknowns_in_col(board* p, int col) {
    int count = 0;
    for (int r = 0; r < BSIZE; r++) {
        if (p->f[r][col] == unknown) {
            count++;
        }
    }
    return count;
}

// Helper function: Check if cell is valid and has a tree (4-connected)
bool has_adjacent_tree(board* p, int row, int col) {
    // Check 4 directions: up, down, left, right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    for (int i = 0; i < 4; i++) {
        int nr = row + dr[i];
        int nc = col + dc[i];
        if (nr >= 0 && nr < BSIZE && nc >= 0 && nc < BSIZE) {
            if (p->f[nr][nc] == tree) {
                return true;
            }
        }
    }
    return false;
}

// Helper function: Check if cell is adjacent to a tent (8-connected)
bool has_adjacent_tent(board* p, int row, int col) {
    // Check 8 directions
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    for (int i = 0; i < 8; i++) {
        int nr = row + dr[i];
        int nc = col + dc[i];
        if (nr >= 0 && nr < BSIZE && nc >= 0 && nc < BSIZE) {
            if (p->f[nr][nc] == tent) {
                return true;
            }
        }
    }
    return false;
}

// Rule 1: If a row or column already has the correct number of tents, all unknowns -> grass.
bool full_tents(board* p, bool* changed) {
    for (int r = 0; r < BSIZE; r++) {
        if (count_tents_in_row(p, r) == p->tents_row[r]) {
            for (int c = 0; c < BSIZE; c++) {
                if (p->f[r][c] == unknown) {
                    p->f[r][c] = grass;
                    *changed = true;
                }
            }
        }
    }
    
    for (int c = 0; c < BSIZE; c++) {
        if (count_tents_in_col(p, c) == p->tents_col[c]) {
            for (int r = 0; r < BSIZE; r++) {
                if (p->f[r][c] == unknown) {
                    p->f[r][c] = grass;
                    *changed = true;
                }
            }
        }
    }
    return true;
}

// Rule 2: Any unknown cell not 4-connected to a tree -> grass.
bool not_near_tree(board* p, bool* changed) {
    for (int r = 0; r < BSIZE; r++) {
        for (int c = 0; c < BSIZE; c++) {
            if (p->f[r][c] == unknown && !has_adjacent_tree(p, r, c)) {
                p->f[r][c] = grass;
                *changed = true;
            }
        }
    }
    return true;
}

// Rule 3: If the number of unknown cells equals the number of tents required, all unknowns -> tents.
bool unknown_is_required(board* p, bool* changed) {
    for (int r = 0; r < BSIZE; r++) {
        int tents_needed = p->tents_row[r] - count_tents_in_row(p, r);
        if (tents_needed > 0 && count_unknowns_in_row(p, r) == tents_needed) {
            for (int c = 0; c < BSIZE; c++) {
                if (p->f[r][c] == unknown) {
                    p->f[r][c] = tent;
                    *changed = true;
                }
            }
        }
    }
    
    for (int c = 0; c < BSIZE; c++) {
        int tents_needed = p->tents_col[c] - count_tents_in_col(p, c);
        if (tents_needed > 0 && count_unknowns_in_col(p, c) == tents_needed) {
            for (int r = 0; r < BSIZE; r++) {
                if (p->f[r][c] == unknown) {
                    p->f[r][c] = tent;
                    *changed = true;
                }
            }
        }
    }
    return true;
}

// Rule 4: Any unknown cell 8-connected to a tent -> grass.
bool around_tent(board* p, bool* changed) {
    for (int r = 0; r < BSIZE; r++) {
        for (int c = 0; c < BSIZE; c++) {
            if (p->f[r][c] == unknown && has_adjacent_tent(p, r, c)) {
                p->f[r][c] = grass;
                *changed = true;
            }
        }
    }
    return true;
}

// Rule 5: For any tree and its 4-connected cells, if there is exactly one unknown and zero tents, then that unknown -> tent.
bool near_tree_1_left(board* p, bool* changed) {
    for (int r = 0; r < BSIZE; r++) {
        for (int c = 0; c < BSIZE; c++) {
            if (p->f[r][c] == tree) {
                int dr[] = {-1, 1, 0, 0};
                int dc[] = {0, 0, -1, 1};
                
                int unknown_count = 0;
                int unknown_r = -1, unknown_c = -1;
                bool has_tent_nearby = false;
                
                for (int i = 0; i < 4; i++) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (nr >= 0 && nr < BSIZE && nc >= 0 && nc < BSIZE) {
                        if (p->f[nr][nc] == unknown) {
                            unknown_count++;
                            unknown_r = nr;
                            unknown_c = nc;
                        } else if (p->f[nr][nc] == tent) {
                            has_tent_nearby = true;
                        }
                    }
                }
                
                if (unknown_count == 1 && !has_tent_nearby) {
                    p->f[unknown_r][unknown_c] = tent;
                    *changed = true;
                }
            }
        }
    }
    return true;
}

// Check if board is solved (no unknowns remain)
bool is_solved(board* p) {
    // Check for NULL pointer
    if (p == NULL) {
        return false;
    }

    for (int r = 0; r < BSIZE; r++) {
        for (int c = 0; c < BSIZE; c++) {
            if (p->f[r][c] == unknown) {
                return false;
            }
        }
    }
    return true;
}

// Solve the board using the defined rules
bool solve(board* p) {
    if (p == NULL) {
        return false;
    }

    bool changed = true;
    
    // Keep applying rules until no more changes occur
    while (changed) {
        changed = false;
        
        full_tents(p, &changed);
        not_near_tree(p, &changed);
        unknown_is_required(p, &changed);
        around_tent(p, &changed);
        near_tree_1_left(p, &changed);
    }
    
    // Return true if board is completely solved (no unknowns remain)
    return is_solved(p);
}

// Convert board to string representation
bool board2str(board b, char* s)
{
    // Check for NULL string
    if (s == NULL) {
        return false;
    }
    
    int index = 0;
    
    // Copy board to string with separators
    for (int r = 0; r < BSIZE; r++) {
        for (int c = 0; c < BSIZE; c++) {
            s[index++] = b.f[r][c];
        }
        // Add separator after each row except the last
        if (r < BSIZE - 1) {
            s[index++] = sep;
        }
    }
    
    // Null-terminate the string
    s[index] = '\0';
    
    return true;
}

void test(void) {
    board b;
    char s[BSIZE*(BSIZE+1)];

    // 0. NULL pointer checks
    assert(inputboard(NULL, "111111", "222222", &b) ==false);
    assert(inputboard("*    *|    * |      |  *  *|      | **   ", NULL, "222222", &b) ==false);
    assert(inputboard("*    *|    * |      |  *  *|      | **   ", "111111", NULL, &b) ==false);
    assert(inputboard("*    *|    * |      |  *  *|      | **   ", "111111", "222222", NULL) ==false);

    assert(solve(NULL) == false);
    assert(board2str(b, NULL) == false);

    // 1. FAIL : Empty string
    assert(inputboard("", "111111", "222222", &b) ==false);

    // We only compile these lines if BSIZE has been #defined to be 6
    #if BSIZE == 6
        // 2. FAIL : String too long (extra unknown on 5th line)
        assert(inputboard("*    *|    * |      |  *  *|       | **   ","120121", "201112", &b)==false);
        // 3. FAIL : Size not matching BSIZE
        assert(inputboard("*    *|    * |      |  *  *|      | **   ", "12012", "201112", &b)==false);
        // 4. FAIL : Size not digit in counts
        assert(inputboard("*    *|    * |      |  *  *|      | **   ", "120121", "201a12", &b)==false);
        // 5. FAIL : Invalid counts
        assert(inputboard("*    *|    * |      |  *  *|      | **   ", "120127", "201112", &b)==false);
        // 6. FAIL : Total tens per row (6), not same as per column (7)
        assert(inputboard("*    *|    * |      |  *  *|      | **   ", "120121", "201111", &b)==false);
        // 7.1. FAIL : Invalid square ('N')
        assert(inputboard("*    *|    * |  N   |  *  *|      | **   ", "120121", "201112", &b)==false);
        // 8.2. FAIL : Only unknown or tree squares allowed on input, not grass
        assert(inputboard("*    *|    * | ...  |  *  *|      | **   ", "120121", "201112", &b)==false);
        // 9. FAIL : Missing separator
        assert(inputboard("*    *     * |      |  *  *|      | **   ", "120121", "201112", &b)==false);
        // PASS
        assert(inputboard("*    *|    * |      |  *  *|      | **   ", "120121", "201112", &b)==true);

        // Solvable 1
        assert(inputboard("*    *|    * |      |  *  *|      | **   ", "120121", "201112", &b)==true);
        assert(solve(&b)==true);
        assert(board2str(b, s));
        assert(strcmp("*+..+*|....*.|....+.|.+*..*|.....+|+**+..", s)==0);

        // Solvable 2
        assert(inputboard("   *  |  **  | *    |      |*    *| *    ", "121111", "111202", &b)==true);
        assert(solve(&b)==true);
        assert(board2str(b,s));
        assert(strcmp("...*+.|.+**..|.*.+..|.+...+|*....*|+*+...", s)==0);

        // NOT Solvable
        assert(inputboard("    * |  *   |   *  | *   *|  *   |*     ", "112012", "111121", &b)==true);
        assert(solve(&b)==false);
    #endif

    #if BSIZE == 4
        assert(inputboard("*  *|    |*   |   *", "1111", "1102", &b)==true);
        assert(solve(&b)==true);
        assert(board2str(b,s));
        assert(strcmp("*+.*|...+|*...|+.+*", s)==0);
    #endif
}
