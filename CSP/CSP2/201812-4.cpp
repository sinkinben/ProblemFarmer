#include<iostream>
#include<algorithm>
#define MAX_N 50001
#define MAX_M 100001 
using namespace std;
struct Edge{
	int a=-1, b=-1;
	int cost = -1;
	bool operator < (const Edge &e) const{
		return cost < e.cost;
	}
};
int n,m,root;
int tree[MAX_N]={0};
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
	cin>>n>>m>>root;
	for(int i=1;i<=m;i++)
		cin>>edge[i].a>>edge[i].b>>edge[i].cost;
	sort(edge+1,edge+m+1);
	for(int i=1;i<=n;i++)
		tree[i]=-1;
	int max_cost = INT_MIN;
	for(int i=1;i<=m;i++)
	{
		int a = findRoot(edge[i].a);
		int b = findRoot(edge[i].b);
		if(a!=b)
		{
			tree[a]=b;
			if(max_cost < edge[i].cost)
				max_cost = edge[i].cost;
		}
	}
	cout<<max_cost<<endl;
}


