#include<iostream>
#include<vector>
#include<string.h>
#define VMAX	100
#define EMAX	100
using namespace std;
vector<int> edge[VMAX];
int n,m;
bool vis[VMAX]={0};
void DFS(int now)
{
	vis[now]=1;
	cout<<now<<' ';
	for(int x:edge[now])
	{
		if(!vis[x])
			DFS(x);
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=0;i<=n;i++)
		edge[i].clear();
	int a,b;
	for(int i=0;i<m;i++)
	{
		cin>>a>>b;
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	cout<<"DFS"<<endl;
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		cout<<i<<": ";
		DFS(i);
		cout<<endl;
	}
}


