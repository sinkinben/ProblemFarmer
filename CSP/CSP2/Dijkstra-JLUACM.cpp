#include<queue>
#include<iostream>
#include<string.h>
#define ENUM	100
#define VNUM	100
using namespace std;
const int INF=0x3f3f3f3f;
int cost[ENUM], dist[VNUM];
int e;
int pnt[ENUM], nxt[ENUM];
int head[VNUM];
int _prev[VNUM], vis[VNUM];
struct qnode{
	int v;
	int cost;
	qnode(int vv=0, int cc=0):v(vv), cost(cc){}
	bool operator <(const qnode& node) const {return cost>node.cost;}; 
};
inline void addEdge(int u, int v, int c)
{
	pnt[e]=v, cost[e]=c, nxt[e]=head[u];
	head[u]=e++;
}
void init(int nv, int ne)
{
	int i,u,v;
	int c;
	e=0;
	memset(head,-1,sizeof(head));
	memset(vis,0,sizeof(vis));
	memset(_prev,-1,sizeof(_prev));
	
	for(i=0;i<nv;i++)	
		dist[i]=INF;
	for(i=0;i<ne;i++)
	{
		scanf("%d %d %d", &u, &v, &c);
		addEdge(u,v,c);
	}
}
void dij(int n, const int src)
{
	qnode mv;
	int i,j,k,pre;
	priority_queue<qnode> que;
	vis[src]=1;
	dist[src]=0;
	que.push(qnode(src,0));
	for(pre=src, i=1;i<n;i++)
	{
		for(j=head[pre];j!=-1;j=nxt[j])
		{
			k=pnt[j];
			if(vis[k]==0 && dist[pre]+cost[j]<dist[k])
			{
				dist[k]=dist[pre]+cost[j];
				que.push(qnode(pnt[j],dist[k]));
				_prev[k]=pre;
			}
		}
		while(!que.empty() && vis[que.top().v]==1)
			que.pop();
		if(que.empty())
			break;
		mv=que.top();que.pop();
		vis[pre=mv.v]=1;
	}
}
int main()
{
	//顶点编号：0, ..., n-1 
	ios::sync_with_stdio(0);
	int nv=6,ne=8;
	init(nv,ne);
	dij(nv,0);
	for(int i=1;i<nv;i++)
		cout<<dist[i]<<' ';
	//dist[i]为src到i的短距离 
}


