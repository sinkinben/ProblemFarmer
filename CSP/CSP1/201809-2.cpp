#include<bits/stdc++.h>
using namespace std;
bool H[1000001]={0};
int N=0;
int main()
{
	ios::sync_with_stdio(false);
	cin>>N;
	int a,b;
	int ans=0;
	for(int i=0;i<N;i++)
	{
		cin>>a>>b;
		for(int j=a;j<=b-1;j++)
			H[j]=true;
	}
	for(int i=0;i<N;i++)
	{
		cin>>a>>b;
		for(int j=a;j<=b-1;j++)
			ans+=H[j];
	}
	cout<<ans;
}
