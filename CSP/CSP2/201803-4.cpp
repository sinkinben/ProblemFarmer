#include<iostream>
/*
	Alice=1, Bob=2
*/

using namespace std;
int a[4][4]={{0}};
int T;
static int zeroNum=0;
void input()
{
	zeroNum=0;
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			cin>>a[i][j];
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			zeroNum+=(a[i][j]==0);
}
bool check(int user)
{
	//check row and col
	for(int i=1;i<=3;i++)
	{
		if(a[i][1]==user && a[i][1]==a[i][2] &&
		   a[i][1]==a[i][3])
		   return true;
		if(a[1][i]==user && a[1][i]==a[2][i] &&
		   a[1][i]==a[3][i])
		   return true;
	}
	if((a[1][1]==user && a[1][1]==a[2][2] && a[1][1]==a[3][3])
	 ||(a[1][3]==user && a[1][3]==a[2][2] && a[1][3]==a[3][1]))
		return true;
	return false;
		
}
int dfs(int user)
{
	if(user==1 && check(2))
		return -(zeroNum+1);
	else if(user==2 && check(1))
		return zeroNum+1;
	else if(zeroNum==0)
		return 0;
	int alice=INT_MIN;
	int bob=INT_MAX;
	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<=3;j++)
		{
			if(a[i][j]==0)
			{
				a[i][j]=user;
				zeroNum--;
				//try something here
				if(user==1)
					alice=max(alice,dfs(2));
				else if(user==2)
					bob=min(bob,dfs(1));
				////////////////////////////
				a[i][j]=0;
				zeroNum++;
			}
		}
	}
	/////此处的if-else不太理解 
	if(user==1)
		return alice;
	else 
		return bob;	
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--)
	{
		input();
		if(check(2))
		{
			cout<<-(zeroNum+1)<<endl;
			continue;
		}
		cout<<dfs(1)<<endl;
	}
}


