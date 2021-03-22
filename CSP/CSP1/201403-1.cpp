#include<bits/stdc++.h>
using namespace std;
int a[501];
int n;
int main()
{
	memset(a,0,sizeof(a));
	cin>>n;
	int t;
	for(int i=0;i<n;i++)
	{
		cin>>t;
		a[abs(t)]++;
	}
	
	int count=0;
	for(int i=1;i<=501;i++)
	{
		if(a[i]==2)
			count++;
	}
	cout<<count<<endl;
	return 0;
}
