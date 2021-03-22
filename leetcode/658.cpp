#include "leetcode.h"
#include <cmath>
#define dist(a, x) (abs((a) - (x)))
class Solution
{
public:
    vector<int> findClosestElements(vector<int> &arr, int k, int x)
    {
        if (x <= arr.front())
        {
            vector<int> v(arr.begin(), arr.begin() + k);
            return v;
        }
        else if (x >= arr.back())
        {
            int size = arr.size();
            vector<int> v(arr.begin() + (size - k), arr.end());
            return v;
        }
        int i = 0;
        while (arr[i] < x)
            i++;
        //now, arr[i]>=x
        if (dist(arr[i - 1], x) <= dist(arr[i], x))
            i--;
        k--;
        int l = i - 1, r = i + 1;
        printf("%d %d %d\n", l, i, r);
        bool lend = false;
        bool rend = false;
        while (k)
        {
            printf("dist ---- %d %d\n", dist(arr[l], x), dist(arr[r], x));
            printf("%d %d\n", l, r);
            printf("arr,l,r --- %d %d\n\n", arr[l], arr[r]);
            if (l >= 0 && dist(arr[l], x) <= dist(arr[r], x))
            {
                l--;
                k--;
                if (l == -1)
                {
                    lend = true;
                    break;
                }
            }
            else if (r <= (arr.size() - 1) && dist(arr[r], x) < dist(arr[l], x))
            {
                r++;
                k--;
                if (r == arr.size())
                {
                    rend = true;
                    break;
                }
            }
        }
        printf("K=%d\n", k);
        if (lend)
        {
            while (k)
                r++, k--;
        }
        if (rend)
        {
            while (k)
                l--, k--;
        }

        vector<int> v(arr.begin() + l + 1, arr.begin() + r);
        return v;
    }
};

int main()
{
    int a[] = {0, 1, 1, 1, 2, 3, 6, 7, 8, 9};
    vector<int> v(a, a + 10);
    for (int x : v)
        printf("%d ", x);
    puts("");
    int k = 9, x = 4;
    Solution sol;
    auto vv = sol.findClosestElements(v, k, x);
    for (int x : vv)
        printf("%d ", x);
}
