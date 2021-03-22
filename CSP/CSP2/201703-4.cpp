/*
	边按权值升序排列 
	每添加一条边，使用并查集判断是否联通 
	连通时，当前边的权值即是所求的天数 
*/
#include<iostream>
#include<algorithm>
#define MAXN 100001
#define MAXM 200001
using namespace std;
struct Edge{
	int a=-1,b=-1,c=-1;
	bool operator <(const Edge &e) const
	{
		return c<e.c;
	}
};
Edge edge[MAXM];
int edgelen=0;
int tree[MAXN]={0};
int n,m;

int findRoot(int x)
{
	if(tree[x]==-1)
		return x;
	else
		return tree[x]=findRoot(tree[x]); 
}

int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>m;
	while(m--)
	{
		cin>>edge[edgelen].a
		   >>edge[edgelen].b
		   >>edge[edgelen].c;
		edgelen++;
	} 
	sort(edge,edge+edgelen);
	for(int i=0;i<=n;i++)
		tree[i]=-1;
	for(int i=0;i<edgelen;i++)
	{
		int a=findRoot(edge[i].a);
		int b=findRoot(edge[i].b);
		if(a!=b)
			tree[a]=b;
		if(findRoot(1)==findRoot(n))
		{
			cout<<edge[i].c<<endl;
			break;
		}
	}
	 
}


