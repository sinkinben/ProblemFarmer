#include<bits/stdc++.h>
using namespace std;
bool a[10001];
int n;
int main()
{
	cin>>n;
	memset(a,0,sizeof(a));
	int t;
	for(int i=1;i<=n;i++)
	{
		cin>>t;
		a[t]=true;
	}
	
	int count=0;
	for(int i=1;i<=10000;i++)
	{
		if(a[i]&&a[i-1])
			count++;
	}
	cout<<count<<endl;
	return 0;
}
