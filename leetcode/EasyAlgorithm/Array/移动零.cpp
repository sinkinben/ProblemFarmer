class Solution
{
public:
    void moveZeroes(vector<int> &nums)
    {
        func2(nums);
    }
    void func2(vector<int> &nums)
    {
        int n = nums.size();
        int i = 0;
        int zero = 0;
        for (int x : nums)
        {
            if (x != 0)
                nums[i++] = x;
            else
                zero++;
        }
        while (zero--)
            nums[i++] = 0;
    }
    // 扫描，遇到 0 删除之，同时计算 0 的个数
    void func1(vector<int> &nums)
    {
        const auto ibegin = nums.begin();
        int k = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == 0)
            {
                k++;
                nums.erase(ibegin + i);
                i--;
            }
        }
        while (k--)
            nums.push_back(0);
    }
};