/*
	BFS版本
	还是65
	超时 
*/
#include<iostream>
#include<string.h>
#include<queue>
#include<vector>
#include<set>
#define VMAX 1001
#define EMAX 10001
using namespace std;
int n,m;
bool vis[VMAX]={0};
vector<int> edge[VMAX];
set<int> knows[VMAX];
void bfs(vector<int> &v,int start)
{
	memset(vis,0,sizeof(vis));
	queue<int> q;
	int now;
	q.push(start);
	vis[start]=1;
	//cout<<start<<' ';
	v.push_back(start);
	while(!q.empty())
	{
		now=q.front();
		q.pop();
		for(int x:edge[now])
		{
			if(!vis[x])
			{
				vis[x]=1;
				//cout<<x<<' ';
				v.push_back(x);
				q.push(x);
			}
		}
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
	}
	for(int i=1;i<=n;i++)
	{
		vector<int> v;
		bfs(v,i);
		int size = v.size();
		for(int j=1;j<size;j++)
		{
			knows[v[0]].insert(v[j]);
			knows[v[j]].insert(v[0]);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		ans+=(knows[i].size()==(n-1));
	cout<<ans<<endl;
}
 
