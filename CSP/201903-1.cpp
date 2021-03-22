#include <iostream>
#include <vector>
#include <set>
#include <cmath>
using namespace std;
vector<int> nums;
int main()
{
    ios::sync_with_stdio(0);
    int n;
    cin >> n;
    cin.ignore();
    nums.resize(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];
    cout << max(nums.back(), nums.front()) << ' ';
    if (n % 2)
    {
        cout << nums[n / 2] << ' ';
    }
    else
    {
        int k = (nums[n / 2] + nums[(n / 2) - 1]);
        cout << (double)k / 2 << ' ';
    }
    cout << min(nums.front(), nums.back());
}
