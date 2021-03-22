#include "leetcode.h"
class Solution
{
public:
    int rows = 0, cols = 0;
    bool exist(vector<vector<char>> &board, string word)
    {
        if (board.size() == 0 || board[0].size() == 0)
            return word.length() == 0;
        rows = board.size(), cols = board[0].size();
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (word[0] == board[i][j] && dfs(board, word, 1, i, j))
                    return true;
            }
        }
        return false;
    }

    bool dfs(vector<vector<char>> &b, const string &word, int idx, int x, int y)
    {
        if (idx == (int)word.length())
            return true;
        char tmp = b[x][y], target = word[idx++];
        b[x][y] = '.';
        if (x + 1 < rows && b[x + 1][y] == target && dfs(b, word, idx, x + 1, y))
            return true;
        if (x - 1 >= 0 && b[x - 1][y] == target && dfs(b, word, idx, x - 1, y))
            return true;
        if (y + 1 < cols && b[x][y + 1] == target && dfs(b, word, idx, x, y + 1))
            return true;
        if (y - 1 >= 0 && b[x][y - 1] == target && dfs(b, word, idx, x, y - 1))
            return true;
        b[x][y] = tmp;
        return false;
    }
};