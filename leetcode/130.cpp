#include "leetcode.h"
#include <queue>

class Solution
{
public:
    const vector<vector<int>> direction = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int row, col;
    void solve(vector<vector<char>> &board)
    {
        row = board.size();
        if (row == 0)
            return;
        col = board[0].size();

#define func bfs
        for (int j = 0; j < col; j++)
        {
            if (board[0][j] == 'O')
                func(0, j, board);
            if (board[row - 1][j] == 'O')
                func(row - 1, j, board);
        }

        for (int i = 0; i < row; i++)
        {
            if (board[i][0] == 'O')
                func(i, 0, board);
            if (board[i][col - 1] == 'O')
                func(i, col - 1, board);
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                if (board[i][j] == 'Y')
                    board[i][j] = 'O';
            }
        }
    }

    void dfs(int i, int j, vector<vector<char>> &board)
    {
        board[i][j] = 'Y';
        for (auto &v : direction)
        {
            int a = i + v[0], b = j + v[1];
            if (a < 0 || b < 0 || a >= row || b >= col)
                continue;
            if (board[a][b] == 'O')
                dfs(a, b, board);
        }
    }

    void bfs(int i, int j, vector<vector<char>> &board)
    {
        typedef pair<int, int> node;
        queue<node> q;
        q.push(node(i, j));
        board[i][j] = 'Y';
        while (!q.empty())
        {
            node n = q.front();
            q.pop();
            for (auto &v : direction)
            {
                int a = n.first + v[0], b = n.second + v[1];
                if (!(a < 0 || b < 0 || a >= row || b >= col) && board[a][b] == 'O')
                    board[a][b] = 'Y', q.push(node(a, b));
            }
        }
    }
};

int main()
{
}