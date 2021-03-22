#define getProfit(x, y) (x * boardingCost - y * runningCost)
class Solution
{
public:
    int minOperationsMaxProfit(vector<int> &customers, int boardingCost, int runningCost)
    {
        int waiting = 0;
        int finish = 0;
        int p = -1;
        int maxi = 1;
        int i = 1;
        for (int x : customers)
        {
            waiting += x;
            bool flag = waiting >= 4;
            finish += (flag ? 4 : waiting);
            waiting = (flag ? waiting - 4 : 0);
            int t = getProfit(finish, i);
            if (p < t)
            {
                p = t;
                maxi = i;
            }
            i++;
        }
        while (waiting != 0)
        {
            bool flag = waiting >= 4;
            finish += (flag ? 4 : waiting);
            waiting = (flag ? waiting - 4 : 0);
            int t = getProfit(finish, i);
            if (p < t)
            {
                p = t;
                maxi = i;
            }
            i++;
        }
        return p > 0 ? maxi : -1;
    }
};