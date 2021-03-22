class Solution
{
public:
    int convertInteger(int A, int B)
    {
        unsigned int n = A ^ B;
        int k = 0;
        while (n)
            k++, n &= (n - 1);
        return k;
    }
};