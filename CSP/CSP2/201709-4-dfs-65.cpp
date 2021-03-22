/*
	65分版本
	DFS
	运行超时 
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
vector<int> edge[MAXN];
set<int> knows[MAXN];
void dfs(vector<int> &v, int now)
{
	vis[now]=1;
	v.push_back(now);
	for(int x:edge[now])
	{
		if(!vis[x])
			dfs(v,x);
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
		vector<int> v;
		dfs(v,i);
		int size = v.size();
		for(int i=1;i<size;i++)
		{
			knows[v[0]].insert(v[i]);
			knows[v[i]].insert(v[0]);
		}
	}
	int ans=0;
	for(int i=1;i<=N;i++)
		ans+=(knows[i].size()==(N-1));
	cout<<ans<<endl;
	
}


