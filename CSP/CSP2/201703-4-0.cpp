/*
6 8
0 2 10
0 4 30
0 5 100
1 2 5
2 3 50
3 5 10
4 3 20
4 5 60
*/
/*
	错误：认为是最短路径上的最大边 
	解释：以题目例子进行改造 
	第一种经过的枢纽依次为1, 2, 3, 6，所需要的时间分别是1, 1, 7，则整条地铁线需要7天修完；
　　第二种经过的枢纽依次为1, 4, 5, 6，所需要的时间分别是2, 5, 6，则整条地铁线需要6天修完。
	第一种是最短路径，但是根据题意，仍是选择第二种路径。 
*/
#include<queue>
#include<iostream>
#include<string.h>
#define ENUM    200000 
#define VNUM    100000 
using namespace std;
struct Box{
	int a=-1,b=-1;
	int cost=-1;
};
Box box[ENUM];
static int boxlen=0;
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
		u--,v--;
        addEdge(u,v,c);
        box[boxlen].a = u;
        box[boxlen].b = v;
        box[boxlen++].cost = c;
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

void path(vector<int> &v,int k)
{
	if(k==-1)
		return;
	else
	{
		path(v,_prev[k]);
		//cout<<"->"<<k;
		v.push_back(k);
	}
}

int main()
{
    //顶点编号：0, ..., n-1 
    ios::sync_with_stdio(0);
    int nv,ne;
    cin>>nv>>ne;
    init(nv,ne);
    dij(nv,0);
    //for(int i=1;i<nv;i++)
    //    cout<<dist[i]<<' ';
    //dist[i]为src到i的短距离 
    //cout<<endl;
    int ans=INT_MIN;
	vector<int> v;
	path(v,nv-1);
	
	int size = v.size();
	for(int i=1;i<size;i++)
	{
		int a = v[i-1];
		int b = v[i];
		for(int j=0;j<boxlen;j++)
		{
			if(box[j].a==a && box[j].b==b)
			{
				ans = max(ans,box[j].cost);
				break;
			}
		}
	} 
	
	cout<<ans<<endl;
}

