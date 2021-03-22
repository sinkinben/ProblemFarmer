#include<iostream>
#include<cmath> 
using namespace std;
int main()
{
	int n,m;
	cin>>n>>m;
	int a[n][m];
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
			cin>>a[i][j];
	}
	
	for(i=0;i<=n-3;i++)
	{
		for(j=0;j<m;j++)
		{
			if(abs(a[i][j])==abs(a[i+1][j]) && abs(a[i][j])==abs(a[i+2][j]))
			{
				if(a[i][j]>0)
					a[i][j]=-a[i][j];
				if(a[i+1][j]>0)
					a[i+1][j]=-a[i+1][j];
				if(a[i+2][j]>0)
					a[i+2][j]=-a[i+2][j];
			}	
		}
	}
	for(j=0;j<=m-3;j++)
	{
		for(i=0;i<n;i++)
		{
			if(abs(a[i][j])==abs(a[i][j+1]) && abs(a[i][j])==abs(a[i][j+2]))
			{
				if(a[i][j]>0)
					a[i][j]=-a[i][j];
				if(a[i][j+1]>0)
					a[i][j+1]=-a[i][j+1];
				if(a[i][j+2]>0)
					a[i][j+2]=-a[i][j+2]; 
			} 
		} 
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			if(a[i][j]>0)
				cout<<a[i][j]<<' ';
			else
				cout<<0<<' ';
		}
		cout<<endl;
	}
}


