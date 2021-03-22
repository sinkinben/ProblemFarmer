#include <cstdio>
#include <cmath>
#define max(a, b) ((a) > (b)) ? (a) : (b)
#define min(a, b) ((a) < (b)) ? (a) : (b)
int A(int *nums, int start, int end)
{
    if (start == end)
        return nums[start];
    else if (start == end - 1)
        return max(nums[start], nums[end]);
    else
    {
        int a = nums[start] + A(nums, start + 2, end);
        int b = nums[start] + A(nums, start + 1, end - 1);
        int c = nums[end] + A(nums, start + 1, end - 1);
        int d = nums[end] + A(nums, start, end - 2);
        return max(min(a,b), min(c,d));
    }
}
bool PredictTheWinner(int *nums, int numsSize)
{
    int sum = 0;
    for (int i = 0; i < numsSize; i++)
        sum += nums[i];
    int a = A(nums, 0, numsSize - 1);
    printf("%d %d\n", a, sum);
    return a >= (sum - a);
}

int main()
{
    int a[] = {1, 5, 2};
    printf("%d\n", PredictTheWinner(a, 3));
}
