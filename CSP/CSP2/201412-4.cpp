#include<iostream>
#include<bits/stdc++.h>
#define MAX_N 1001
#define MAX_M 100001
using namespace std;
struct Edge{
	int a=-2, b=-2;
	int cost = -2;
	bool operator < (const Edge &e) const
	{
		return cost < e.cost;
	}
};
int n,m;
int tree[MAX_N];
Edge edge[MAX_M];
int findRoot(int x)
{
	int tmp;
	if(tree[x]==-1)
		return x;
	else 
	{
		tmp = findRoot(tree[x]);
		tree[x] = tmp;
		return tmp;
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>edge[i].a>>edge[i].b>>edge[i].cost;
	sort(edge+1,edge+1+m);
	for(int i=1;i<=n;i++)
		tree[i]=-1;
	int ans=0;
	for(int i=1;i<=m;i++)
	{
		int a = findRoot(edge[i].a);
		int b = findRoot(edge[i].b);
		if(a!=b)
		{
			tree[a]=b;
			ans+=edge[i].cost;
		}
	}
	cout<<ans<<endl;
	
}


