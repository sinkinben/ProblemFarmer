#include "leetcode.h"
class Solution
{
public:
    bool isMonotonic(vector<int> &A)
    {
        int len = A.size();
        int flag = 0;
        int i = 0;
        if (len == 1)
            return true;
        while (i < len && A[i] == A[0])
            i++;
        if (i == len)
            return true;
        flag = A[i] - A[i - 1];

        if (flag > 0)
        {
            for (int k = i; k < len; k++)
            {
                if (A[k] < A[k - 1])
                    return false;
            }
        }
        else
        {
            for (int k = i; k < len; k++)
            {
                if (A[k] > A[k - 1])
                    return false;
            }
        }

        return true;
    }
};
int main()
{
    int a[] = {1, 1, 1};
    vector<int> v(a, a + 3);
    Solution sol;
    printf("%d\n", sol.isMonotonic(v));
}