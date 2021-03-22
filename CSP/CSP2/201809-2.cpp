#include<bits/stdc++.h>
using namespace std;
bool h[1000001]={false};
int main()
{
	int n;
	cin>>n;
	int a,b;
	int ans=0;
	for(int i=0;i<n;i++)
	{
		cin>>a>>b;
		for(int j=a;j<b;j++)
			h[j]=true;
	}
	for(int i=0;i<n;i++)
	{
		cin>>a>>b;
		for(int j=a;j<b;j++)
			ans+=h[j];
	}
	cout<<ans<<endl;
}
