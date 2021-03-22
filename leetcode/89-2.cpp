#include "leetcode.h"
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> v;
        if(n==0)
        {
        	v.push_back(0);
        	return v;
		}
		if(n==1)
		{
			v.push_back(0);
			v.push_back(1);
			return v;
		}
		
		v.push_back(0);
		v.push_back(1);
		for(int i=1;i<n;i++)
		{
			this->helper(v,i);
		}
		
		return v;
    }
    
    void helper(vector<int> &v, int validBits)
    {
    	const vector<int> v0(v);
    	int len=v0.size();
    	for(int i=len-1;i>=0;i--)
    		v.push_back(v0[i]);
    	// [0...len-1] + [len ... 2*len-1]
    	for(int i=len;i<2*len;i++)
    	{
    		v[i]=v[i]|(1<<validBits);
		}
	}
};