#include "leetcode.h"
#include <cassert>
#include <deque>
class Solution
{
public:
    int empty = 0;
    vector<pair<int, int>> pos;
    vector<vector<char>> *result;
    void solveSudoku(vector<vector<char>> &board)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] == '.')
                    pos.push_back(pair<int, int>(i, j));
            }
        }
        backTrack(pos, pos.begin(), board);
        board.swap(*result);
        delete result;
    }

    void backTrack(vector<pair<int, int>> &pos, vector<pair<int, int>>::iterator itor, vector<vector<char>> &board)
    {
        if (itor == pos.end())
        {
            result = new vector<vector<char>>(board);
            return;
        }
        assert(board[itor->first][itor->second] == '.');
        int r = itor->first;
        int c = itor->second;
        for (int i = 1; i <= 9; i++)
        {
            board[r][c] = '0' + i;
            if (check(r, c, board))
            {
                backTrack(pos, itor + 1, board);
            }
        }
        board[r][c] = '.';
    }

    bool check(int row, int col, vector<vector<char>> &board)
    {
        assert(board[row][col] != '.');
        char x = board[row][col];
        //check row
        for (int j = 0; j < col; j++)
        {
            if (board[row][j] == x)
                return false;
        }
        for (int j = col + 1; j < 9; j++)
        {
            if (board[row][j] == x)
                return false;
        }
        //check col
        for (int i = 0; i < row; i++)
        {
            if (board[i][col] == x)
                return false;
        }
        for (int i = row + 1; i < 9; i++)
        {
            if (board[i][col] == x)
                return false;
        }

        //check square
        int r = row - (row % 3);
        int c = col - (col % 3);
        for (int i = r; i < r + 3; i++)
        {
            for (int j = c; j < c + 3; j++)
                if (i != row && j != col && board[i][j] == x)
                    return false;
        }
        return true;
    }
};

int main()
{
}