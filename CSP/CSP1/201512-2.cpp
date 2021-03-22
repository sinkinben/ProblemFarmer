#include<bits/stdc++.h>
using namespace std;
int n=0,m=0;
int a[30][30]; 
void print()
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(a[i][j]>0)
				cout<<a[i][j]<<' ';
			else 
				cout<<"0 ";
		}
		cout<<endl;
	}
}

int main()
{
	memset(a,0,sizeof(a));
	cin>>n>>m;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>a[i][j];
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<=m-3;j++)
		{
			if(abs(a[i][j+1])==abs(a[i][j]) && abs(a[i][j+2])==abs(a[i][j]))
			{
				if(a[i][j]>0)	a[i][j]=-a[i][j];
				if(a[i][j+1]>0)	a[i][j+1]=-a[i][j+1];
				if(a[i][j+2]>0)	a[i][j+2]=-a[i][j+2];
			}
		}
	}
	
	for(int j=0;j<m;j++)
	{
		for(int i=0;i<=n-3;i++)
		{
			if(abs(a[i+1][j])==abs(a[i][j]) && abs(a[i+2][j])==abs(a[i][j]))
			{
				if(a[i][j]>0)	a[i][j]=-a[i][j];
				if(a[i+1][j]>0)	a[i+1][j]=-a[i+1][j];
				if(a[i+2][j]>0)	a[i+2][j]=-a[i+2][j];
			}
		}
	}
	
	print();
}
