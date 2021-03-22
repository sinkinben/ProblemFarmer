#include<bits/stdc++.h>
using namespace std;
int n=0;
int a[1000]={0};
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	
	int gap=INT_MAX;
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			gap = min(gap, abs(a[j]-a[i]));
		}
	}
	cout<<gap<<endl;
	return 0;
}
