#include "leetcode.h"
#include <map>
class Solution
{
public:
    int findJudge(int N, vector<vector<int>> &trust)
    {
        vector<int> in(N+1), out(N+1);
        for (vector<int> &v : trust)
        {
            out[v[0]]++;
            in[v[1]]++;
        }
        for (int i=1;i<=N;i++)
        {
            if (in[i]==N-1 && out[i]==0)
                return i;
        }
        return -1;
    }
};

int main()
{
    vector<int> v(10);
    for (int x:v)
        printf("%d",x);
}