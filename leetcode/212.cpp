#include "leetcode.h"
struct TrieNode
{
    vector<TrieNode *> links;
    bool isend;
    string word;
    TrieNode() : isend(false), word("") { links.resize(26, nullptr); }
    bool contains(char c) { return links[c - 'a'] != nullptr; }
    void put(char c) { links[c - 'a'] = new TrieNode(); }
    TrieNode *get(char c) { return links[c - 'a']; }
};
class Solution
{
public:
    TrieNode *root = new TrieNode();
    vector<string> result;
    int row, col;
    vector<string> findWords(vector<vector<char>> &board, vector<string> &words)
    {
        if (board.size() == 0 || board[0].size() == 0)
            return result;
        buildTrieTree(words);
        row = board.size();
        col = board[0].size();
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                dfs(board, root, i, j);
            }
        }
        return result;
    }

    void dfs(vector<vector<char>> &board, TrieNode *p, int x, int y)
    {
        char ch = board[x][y];
        if (ch == '.' || !p->contains(ch))
            return;
        p = p->get(ch);
        if (p->isend && p->word != "")
        {
            result.push_back(p->word);
            p->word = "";
        }

        board[x][y] = '.';
        if (x - 1 >= 0)
            dfs(board, p, x - 1, y);
        if (x + 1 < row)
            dfs(board, p, x + 1, y);
        if (y + 1 < col)
            dfs(board, p, x, y + 1);
        if (y - 1 >= 0)
            dfs(board, p, x, y - 1);
        board[x][y] = ch;
    }

    void buildTrieTree(vector<string> &vs)
    {
        for (auto &x : vs)
        {
            auto cur = root;
            for (char c : x)
            {
                if (!cur->contains(c))
                    cur->put(c);
                cur = cur->get(c);
            }
            cur->isend = true, cur->word = x;
        }
    }
};
// int main()
// {
// }