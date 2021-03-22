class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        return func2(nums, target);
    }
    // hash
    vector<int> func2(vector<int> &v, int t)
    {
        unordered_map<int, int> m;
        int n = v.size();
        for (int i = 0; i < n; i++)
        {
            if (m.count(t - v[i]) != 0)
                return vector<int>({i, m[t - v[i]]});
            m[v[i]] = i;
        }
        return vector<int>();
    }
    // force
    vector<int> func1(vector<int> &v, int t)
    {
        int n = v.size();
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (v[i] + v[j] == t)
                    return vector<int>({i, j});
            }
        }
        return vector<int>();
    }
};