#include<bits/stdc++.h>
using namespace std;
int h[1000]={0};
int dp[1000]={0};
int n=0;
//1000000007
//2147483647
int helper(int end)
{
	int minh=h[end];
	int maxs=h[end];
	for(int i=end-1;i>=0;i--)
	{
		if(minh>h[i])	
			minh=h[i];
		int s=(end-i+1)*minh;
		if(s>maxs)
			maxs=s;
	}
	return maxs;
}

int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>h[i];
	dp[0]=h[0];
	for(int i=1;i<n;i++)
	{
		dp[i]=helper(i);
	}
	int max=INT_MIN;
	for(int i=0;i<n;i++)
	{
		if(dp[i]>max)
			max=dp[i];
	}
	cout<<max<<endl;
} 
