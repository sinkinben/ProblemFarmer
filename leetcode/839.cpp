#include "leetcode.h"
#include <algorithm>
class Solution
{
public:
    vector<int> root;
    int numSimilarGroups(vector<string> &A)
    {
        int N = A.size();
        root.resize(N, -1);

        for (int i = 0; i < N; i++)
        {
            for (int j = i + 1; j < N; j++)
            {
                if (similar(A[i], A[j]))
                    merge(i, j);
            }
        }
        return count(root.begin(), root.end(), -1);
    }

    int find(int x)
    {
        return root[x] == -1 ? (x) : (root[x] = find(root[x]));
    }

    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x != y)
            root[y] = x;
    }

    bool similar(const string &a, const string &b)
    {
        int len = min(a.length(), b.length());
        int diff = 0;
        for (int i = 0; i < len; i++)
            diff += (a[i] != b[i]);
        return diff <= 2;
    }
};

