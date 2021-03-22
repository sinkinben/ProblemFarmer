#include "leetcode.h"
class Solution {
public:
    vector<string> v;
    vector<string> generateParenthesis(int n) {
        string s="";
        for(int i=0;i<n;i++)
        	s.append(1,'(');
        for(int i=0;i<n;i++)
        	s.append(1,')');
        v.push_back(s);
        while(next_permutation(s.begin(),s.end()))
        {
        	if(this->check(s))
        		v.push_back(s);
		}
		return v;
    }
    
    bool check(string &s)
    {
    	int flag=0;
    	int len=s.length();
    	for(int i=0;i<len;i++)
    	{
    		if(s[i]=='(')
    			flag++;
    		else if(s[i]==')')
    			flag--;
    		if(flag<0)
    			return false;
		}
		return flag==0;
	}
};