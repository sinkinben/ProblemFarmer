#include "leetcode.h"
#include <map>
class Solution
{
public:
    bool result = false;
    map<char, vector<pair<int, int>>> dict;
    bool exist(vector<vector<char>> &board, string word)
    {
        if (word.length() == 0)
            return true;
        if (board.size() == 0)
            return false;
        for (size_t i = 0; i < board.size(); i++)
        {
            for (size_t j = 0; j < board[i].size(); j++)
            {
                dict[board[i][j]].push_back(pair<int, int>(i, j));
            }
        }
        vector<vector<bool>> flag(board.size(), vector<bool>(board.front().size(), false));
        auto &v = dict[word.front()];
        for (auto &p : v)
        {
            dfs(flag, board, word, 0, p.first, p.second);
            if (result == true)
                return true;
        }
        return false;
    }

    void dfs(vector<vector<bool>> &flag, vector<vector<char>> &board, const string &word, int now, int r, int c)
    {
        // cout << r << ' ' << c << endl;
        if (now == word.length())
        {
            result = true;
            return;
        }
        if (r < 0 || c < 0 || r >= board.size() || c >= board.front().size())
        {
            return;
        }
        if (flag[r][c])
        {
            return;
        }
        if (board[r][c] == word[now])
        {
            flag[r][c] = true;
            dfs(flag, board, word, now + 1, r - 1, c);
            dfs(flag, board, word, now + 1, r + 1, c);
            dfs(flag, board, word, now + 1, r, c - 1);
            dfs(flag, board, word, now + 1, r, c + 1);
            flag[r][c] = false;
        }
        else
        {
            return;
        }
    }
};

int main()
{
    char c[3][4] = {'A', 'B', 'C', 'E', 'S', 'F', 'C', 'S', 'A', 'D', 'E', 'E'};
    vector<vector<char>> board;
    for (int i = 0; i < 3; i++)
    {
        vector<char> v;
        for (int j = 0; j < 4; j++)
        {
            v.push_back(c[i][j]);
        }
        board.push_back(v);
    }

    Solution sol;
    cout << sol.exist(board, "ABCB");
}