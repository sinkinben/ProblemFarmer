/*
	暴力解法 
	0分
	原因不明 
*/ 
#include<iostream>
#include<string>
#include<algorithm>
#include<cmath>
#define MOD 1000000007
using namespace std;
int n;
unsigned long long ans = 0;
bool check1(string &s)
{
	bool flag[4]={0,0,0,0};
	int len = s.length();
	for(int i=0;i<len;i++)
	{
		char c = s[i];
		if('0'<=c && c<='3' && !flag[c-'0'])
			flag[c-'0']=1;	
	}
	return flag[0]==1 && flag[1]==1 && flag[2]==1 && flag[3]==1;
}

bool check2(string &s)
{
	int len = s.length();
	int oneIndex = 0;
	while(s[oneIndex]!='1')
		oneIndex++;
	for(int i=oneIndex+1;i<len;i++)
	{
		if(s[i]=='0')
			return false;
	}
	
	int threeIndex=0;
	while(s[threeIndex]!='3')
		threeIndex++;
	for(int i=threeIndex+1;i<len;i++)
	{
		if(s[i]=='2')
			return false; 
	} 
	return true;
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	unsigned long long num=123*pow(10,n-3);
	while(1)
	{
		string s = to_string(num++);
		int len = s.length();
		if(len>n)
			break;
		if(!check1(s)) continue;
		if(!check2(s)) continue;
		//cout<<s<<endl;
		ans=(ans+1)%MOD;
	}
	cout<<ans<<endl;
	
	 
}


