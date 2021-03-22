#include<bits/stdc++.h>
using namespace std;
int nums[10001];
int n;
int main()
{
	vector<int> v;
	v.push_back(1); 
	memset(nums,0,sizeof(nums));
	int t;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>t;
		nums[t]++;
	}
	int flag=0;
	int max=INT_MIN;
	for(int i=1;i<=10000;i++)
	{
		if(nums[i] > max)
			max=nums[i], flag=i;
	}
	cout<<flag<<endl;
}
