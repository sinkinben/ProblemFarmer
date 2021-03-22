#include "leetcode.h"
class Solution {
public:
	vector<vector<int>> vv;
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> v;
        this->backTrack(0,target,v,candidates);
        
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
    
    void backTrack(int start, int target, vector<int> &v, vector<int> &candidates)
    {
    	for(int i=start;i<candidates.size();i++)
    	{
    		v.push_back(candidates[i]);
    		int n=sum(v);
    		if(n==target)
    			vv.push_back(v);
    		else if(n<target)
    			this->backTrack(i+1,target,v,candidates);
    		v.pop_back();
		}
	}
	
	int sum(vector<int> &v)
	{
		int n=0;
		for(int x:v)
			n+=x;
		return n;
	}
};