#include<iostream>
#include<algorithm>
#define N 101
#define MAX_ENUM 1000
struct Edge{
	int a,b;	//两个顶点 
	int cost;	//权值
	bool operator < (const Edge &e) const
	{
		return cost < e.cost;
	} 
};
int tree[N]={0};
Edge edge[MAX_ENUM];
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
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	int n;	//点数 
	cin>>n;
//	while(cin>>n && n!=0)
	{
		int edges=n*(n-1)/2;	//边数
		cin>>edges; 
		for(int i=1;i<=edges;i++)
			cin>>edge[i].a>>edge[i].b>>edge[i].cost;
		sort(edge+1,edge+edges+1);
		
		for(int i=1;i<=n;i++)
			tree[i]=-1; 
		int ans = 0;
		for(int i=1;i<=edges;i++)
		{
			int a = findRoot(edge[i].a);
			int b = findRoot(edge[i].b);
			if(a!=b)
			{
				tree[a]=b;
				ans+=edge[i].cost;
				cout<<edge[i].a<<' '<<edge[i].b<<' '<<edge[i].cost<<endl;
			}
			printf("%d\n",ans);
		}
	}
}


