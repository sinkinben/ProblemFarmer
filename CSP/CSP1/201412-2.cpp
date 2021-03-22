#include<bits/stdc++.h>
using namespace std;
int a[501][501];
int n=0;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	
	int i=1,j=1;
	cout<<a[i][j]<<' '; 
	while(!(i==n&&j==n))
	{
		//右 1
		if(j<n)
			cout<<a[i][++j]<<' ';
		else 
			cout<<a[++i][j]<<' ';
		
		//左下到左边界
		while(j>=2 && i<n)
		{
			i++, j--;
			cout<<a[i][j]<<' ';
		}
		
		//向下 1
		if(i<n)
			cout<<a[++i][j]<<' ';
		else
			cout<<a[i][++j]<<' ';
		
		//右上 
		while(i>=2 && j<n)
		{
			i--, j++;
			cout<<a[i][j]<<' ';
		}
	}
	return 0;
	
} 
