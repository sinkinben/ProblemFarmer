/*
    暴力穷举法
    但是能通过
    就很迷
 */
#include "leetcode.h"
class Solution {
public:
    string longestPalindrome(string s) {
        int len=s.length();
        if (len == 0)
            return "";
        int start,maxlen=INT_MIN;
        for(int i=0;i<len;i++)
        {
        	for(int j=i;j<len;j++)
        	{
        		if(maxlen<(j-i+1) && this->isPalStr(s,i,j))
        			maxlen=j-i+1, start=i;
        			
			}
		}
		//cout<<start<<' '<<maxlen<<endl;
		string ans="";
		ans.append(s.begin()+start, s.begin()+start+maxlen);
		//cout<<ans<<endl;
		return ans;
    }
    
    bool isPalStr(string &s, int start, int end)
    {
    	int len=(end-start+1);
    	for(int i=0;i<=(len>>1);i++)
    	{
    		if(s[start+i]!=s[end-i])
    			return false;
		}
    	return true;
	}
};