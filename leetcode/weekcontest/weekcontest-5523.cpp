class Solution
{
public:
    int minOperations(vector<string> &logs)
    {
        int k = 0;
        for (auto &s : logs)
        {
            if (s == "./")
                continue;
            else if (s == "../")
            {
                if (k >= 1)
                    k--;
            }
            else
                k++;
        }
        return k;
    }
};