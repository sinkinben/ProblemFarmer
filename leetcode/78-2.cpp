#include "leetcode.h"
class Solution
{
public:
	vector<vector<int>> vv;
	vector<vector<int>> subsets(vector<int> &nums)
	{
		vector<int> v;
		vv.push_back(v);
		int len = nums.size();
		if (len == 0)
			return vv;
		helper(0, v, nums);
		//		for(int i=0;i<vv.size();i++)
		//			print(vv[i]);
		return vv;
	}

	void helper(int start, vector<int> &v, vector<int> &nums)
	{
		for (int i = start; i < nums.size(); i++)
		{
			v.push_back(nums[i]);
			vv.push_back(v);
			helper(i + 1, v, nums);
			v.pop_back();
		}
	}
};