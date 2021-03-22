#include "leetcode.h"
class Solution {
public:
    vector<vector<int>> vv;
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> v;
        this->helper(0,candidates,target,v);
        for(vector<int> &v:vv)
        	sort(v.begin(),v.end());
        set<vector<int>> s;
        for(vector<int> &v:vv)
        	s.insert(v);
        
        vv.clear();
        set<vector<int>>::iterator it;
        for(it=s.begin();it!=s.end();it++)
        	vv.push_back(*it);
        
        return vv;
    }
    
    void helper(int start, vector<int> &nums, int target, vector<int> &v)
    {
    	if(start >= nums.size())
    		return;
    	for(int i=0;i<nums.size();i++)
    	{
    		v.push_back(nums[i]);
    		int flag=judge(v,target);
    		if(flag==0)
    			vv.push_back(v);
			else if(flag==-1)
				this->helper(0,nums,target,v);
			v.pop_back();
		}
    	
	}
	
	int judge(vector<int> &v, int target)
	{
		int n=0;
		for(int x:v)
			n+=x;
		if(n>target)
			return 1;
		if(n==target)
			return 0;
		if(n<target)
			return -1;
	}
};

int main()
{
	
}