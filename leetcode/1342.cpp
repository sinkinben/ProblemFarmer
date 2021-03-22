class Solution
{
public:
    int numberOfSteps(int num)
    {
        int k = 0;
        while (num)
        {
            if (num & 0x1)
                num--;
            else
                num >>= 1;
            k++;
        }
        return k;
    }
};