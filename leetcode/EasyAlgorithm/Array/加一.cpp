class Solution
{
public:
    vector<int> plusOne(vector<int> &digits)
    {
        int n = digits.size() - 1;
        bool flag = false;
        do
        {
            digits[n]++;
            flag = digits[n] >= 10;
            digits[n] %= 10;
            n--;
        } while (flag && n >= 0);
        if (n == -1 && flag)
        {
            digits.insert(digits.begin(), 1);
        }
        return digits;
    }
};