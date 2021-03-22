#include<bits/stdc++.h>
using namespace std;
int m,n;
int a[1000][1000];
int main()
{
	cin>>n>>m;
	memset(a,0,sizeof(a));
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>a[i][j];
	
	for(int j=m-1;j>=0;j--)
	{
		for(int i=0;i<n;i++)
			cout<<a[i][j]<<' ';
		cout<<endl;
	}
	return 0;
}
