#include "leetcode.h"
class Solution {
public:
	vector<vector<int>> vv;
    vector<vector<int>> combine(int n, int k) {
        vector<int> v;
        this->backTrack(n,k,v,1);
        // for(vector<int> &v:vv)
        // 	print(v);
        return vv;
    }
    
    void backTrack(int n, int k, vector<int> &v, int start)
    {
    	for(int i=start;i<=n;i++)
    	{
    		v.push_back(i);
    		if(v.size() == k)
    			vv.push_back(v);
    		else if(v.size() < k)
    			this->backTrack(n,k,v,i+1);
    		v.pop_back();
		}
	}
};
int main()
{
    Solution sol;
    auto vv = sol.combine(13, 13);
    for (auto &v : vv)
    {
        for (auto x : v)
        {
            cout << x << ' ';
        }
        cout << endl;
    }
}