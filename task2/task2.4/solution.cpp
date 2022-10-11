#include <algorithm>
#include <vector>
#include <array>

using namespace std;

class Solution {
    vector<vector<char>> solution;
    vector<vector<vector<size_t>>> is_possible;  // how many blockers for every digit
    bool solved;
    
    bool isKnown(size_t x, size_t y) {
        return solution[x][y] != '.';
    }
    
    bool isPossible(size_t x, size_t y) {
        return solution[x][y] != '.';
    }
    
    void updateCell(size_t x, size_t y, char c) {
        solution[x][y] = c;
    }
    
    size_t& accessPossible(size_t x, size_t y, size_t k) {
        return is_possible[x][y][k];
    }
    
    void blockVariant(size_t x, size_t y, size_t k) {
        for (size_t other_y = 0; other_y < 9; ++other_y) {
            ++accessPossible(x, other_y, k);
        }
        
        for (size_t other_x = 0; other_x < 9; ++other_x) {
            ++accessPossible(other_x, y, k);
        }
        
        for (size_t other_x = x / 3 * 3; other_x < x / 3 * 3 + 3; ++other_x) {
            for (size_t other_y = y / 3 * 3; other_y < y / 3 * 3 + 3; ++other_y) {
                ++accessPossible(other_x, other_y, k);
            }
        }
    }
    
    void unblockVariant(size_t x, size_t y, size_t k) {
        for (size_t other_x = x / 3 * 3; other_x < x / 3 * 3 + 3; ++other_x) {
            for (size_t other_y = y / 3 * 3; other_y < y / 3 * 3 + 3; ++other_y) {
                --accessPossible(other_x, other_y, k);
            }
        }
        
        for (size_t other_x = 0; other_x < 9; ++other_x) {
            --accessPossible(other_x, y, k);
        }
        
        for (size_t other_y = 0; other_y < 9; ++other_y) {
            --accessPossible(x, other_y, k);
        }
    }
    
    void updateResult(size_t index) {
        if (index == 81) {
            solved = true;
            return;
        }
        
        size_t x = index / 9;
        size_t y = index % 9;
        
        if (isKnown(x, y)) {
            updateResult(index + 1);
            return;
        }
        
        for (size_t k = 0; k < 9; ++k) {
            if (accessPossible(x, y, k) != 0) {
                continue;
            }
            
            blockVariant(x, y, k);
            updateCell(x, y, k + '1');
            updateResult(index + 1);
            
            if (solved) {
                return;
            }
            
            unblockVariant(x, y, k);
            updateCell(x, y, '.');
        }
    }
    
public:
    void solveSudoku(vector<vector<char>>& board) {
        solved = false;
        solution = board;
        is_possible = vector<vector<vector<size_t>>>(9, vector<vector<size_t>>(9, vector<size_t>(9, 0)));
        
        for (size_t x = 0; x < 9; ++x) {
            for (size_t y = 0; y < 9; ++y) {
                if (isKnown(x, y)) {
                    blockVariant(x, y, solution[x][y] - '1');
                }
            }
        }
        
        updateResult(0);
        board = solution;
    }
};