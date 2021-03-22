/*
	100分版本
	优化了knows 
*/
#include<iostream>
#include<vector>
#include<string.h>
#include<set>
#define MAXN 1001
#define MAXM 10001
using namespace std;
int N,M; 
bool vis[MAXN]={0};
bool knows[MAXN][MAXN]={{0}};
vector<int> edge[MAXN];
void dfs(int start, int now)
{
	vis[now]=1;
	knows[start][now] = knows[now][start] = 1;
	for(int x:edge[now])
	{
		if(!vis[x])
			dfs(start,x);
	}
	
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>N>>M;
	cin.ignore();
	for(int i=0;i<=N;i++)
		edge[i].clear();
	int a,b;
	for(int i=0;i<M;i++)
	{
		cin>>a>>b;
		edge[a].push_back(b);
	}
	for(int i=1;i<=N;i++)
	{
		memset(vis,0,sizeof(vis));
		dfs(i,i);
	}
	
	int ans=0;
	int i,j;
	for(i=1;i<=N;i++)
	{
		for(j=1;j<=N;j++)
		{
			if(!knows[i][j])
				break;
		}
		ans+=(j==N+1);
	}
	cout<<ans<<endl;
	
}


