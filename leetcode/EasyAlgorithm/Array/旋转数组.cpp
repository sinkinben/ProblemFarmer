#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    void rotate(vector<int> &nums, int k)
    {
        k %= (int)nums.size();
        if (k)
            func2(nums, k);
    }

    // TLE
    void func1(vector<int> &nums, int k)
    {
        while (k--)
        {
            nums.insert(nums.begin(), nums.back());
            nums.pop_back();
        }
    }

    void func2(vector<int> &nums, int k)
    {
        int size = nums.size();
        if (k < size / 2)
        {
            while (k--)
            {
                nums.insert(nums.begin(), nums.back());
                nums.pop_back();
            }
        }
        else
        {
            k = size - k;
            while (k--)
            {
                nums.insert(nums.end(), nums.front());
                nums.erase(nums.begin());
            }
        }
        
    }
};

int main()
{
    vector<int> v = {1, 2, 3};
    Solution sol;
    sol.func2(v, 2);
    for(int x:v)
        cout << x <<' ';
}

/**
 * 1 2 3
 * 1: 3 1 2
 * 2: 2 3 1
 * 3: 1 2 3
 * 4: 3 1 2
 **/