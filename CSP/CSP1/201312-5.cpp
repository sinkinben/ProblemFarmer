#include<bits/stdc++.h>
#define UP(i,j)		(i--)
#define DOWN(i,j)	(i++)
#define LEFT(i,j)	(j--)
#define RIGHT(i,j)	(j++)
using namespace std;
int r=0,c=0;
char grid[50][50];
bool arrive1[50][50];
int si=0,sj=0;
int ti=0,tj=0;
void dfs(int row, int col,bool &flag, bool arrive[50][50]);
void init();
bool can2T(int row,int col,bool &flag);

int main()
{
	init();
	bool t=false;
	dfs(si,sj,t,arrive1);
	if(arrive1[ti][tj]==false)
	{
		cout<<"I'm stuck!"<<endl;
		return 0;
	}
	int ans=0;
	bool arrive2[50][50];
	memset(arrive2,0,sizeof(arrive2));
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
			if(arrive1[i][j])
			{
				bool flag=false;
				dfs(i,j,flag,arrive2);
				memset(arrive2,0,sizeof(arrive2));
				if(flag==false)
					ans++;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
	
}
void init()
{
	memset(grid,0,sizeof(grid));
	memset(arrive1,0,sizeof(arrive1));
	cin>>r>>c;
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
			cin>>grid[i][j];
			if(grid[i][j]=='S')
				si=i,sj=j;
			else if(grid[i][j]=='T')
				ti=i,tj=j;
		}
	}
}
void dfs(int row,int col,bool &flag, bool arrive[50][50])
{
	if(arrive[row][col]||row==-1||row==r||col==-1||col==c)
		return;
	assert(arrive[row][col]==false);
	arrive[row][col]=true;
	switch(grid[row][col])
	{
		case '#':
			arrive[row][col]=false;
			break;
		case 'S':
		case 'T':flag=true;
		case '+':
			dfs(row-1,col,flag,arrive), dfs(row+1,col,flag,arrive), dfs(row,col-1,flag,arrive), dfs(row,col+1,flag,arrive);
			break;
		case '-':
			dfs(row,col-1,flag,arrive), dfs(row,col+1,flag,arrive);
			break;
		case '|':
			dfs(row-1,col,flag,arrive), dfs(row+1,col,flag,arrive);
			break;
		case '.':
			dfs(row+1,col,flag,arrive);
			break;
	}
}

