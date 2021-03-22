#include<bits/stdc++.h>
using namespace std;
bool grid[101][101];
int n=0;
int main()
{
	memset(grid,0,sizeof(grid));
	cin>>n;
	int x1,x2,y1,y2;
	while(n)
	{
		cin>>x1>>y1>>x2>>y2;
		n--;
		
		for(int i=x1;i<=x2-1;i++)
			for(int j=y1;j<=y2-1;j++)
				grid[i][j]=true;
	}
	
	int ans=0;
	for(int i=0;i<101;i++)
		for(int j=0;j<101;j++)
			ans+=(int)grid[i][j];
	cout<<ans<<endl;
	return 0;
	
}
