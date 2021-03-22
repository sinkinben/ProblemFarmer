/**
 * 80分版本
 * 也是套了dijkstra的裸算法
 * type=1, 权值存入c*c
 */
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#define VMAX 10000
typedef unsigned long long ull;
typedef long long ll;
struct Edge
{
    int vex;
    ll cost;
    Edge(int vv=-1, ull cc=-1):vex(vv),cost(cc) {}
};
struct Node
{
    int u;
    ll cost;
    Node(int uu=-1, ll cc=-1):u(uu),cost(cc) {}
    bool operator < (const Node &n) const
    {
        return cost>n.cost;
    }
};
using namespace std;
vector<Edge> graph[VMAX];
priority_queue<Node> q;
ll dist[VMAX]= {0}; //dist[i]是start到i的最短距离
bool vis[VMAX]= {0}; //记录是否被访问
int prevex[VMAX]= {0}; //记录路径的前驱
void dij(int start, int vnum)
{
    memset(prevex,-1,sizeof(prevex));
    memset(vis,0,sizeof(vis));
    for(int i=0; i<=vnum; i++)
        dist[i]=INT_MAX;
    dist[start]=0;
    q.push(Node(start,0));
    Node now;
    while(!q.empty())
    {
        now=q.top();
        q.pop();
        int u=now.u;
        if(!vis[u])
        {
            vis[u]=1;
            //遍历当前节点连接的点
            int len=graph[u].size();
            for(int i=0; i<len; i++)
            {
                int v=graph[u][i].vex;
                ll tempcost=graph[u][i].cost;
                ll nextdist=dist[u]+tempcost;
                if(vis[v])
                    continue;
                if(dist[v] > nextdist)
                {
                    dist[v]=nextdist;
                    q.push(Node(v,nextdist));
                    prevex[v]=u;
                }
                else if(dist[v] == nextdist)
                {
                    //当有多个最短路径时
                }
            }
        }
    }
}
void path(int k)
{
    if(k==-1)
        return;
    else
    {
        path(prevex[k]);
        cout<<"->"<<k;
    }
}
int main()
{
    //顶点从1开始编号
    ios::sync_with_stdio(0);
    int n,m;//点数，边数
    int s,t;
    ll c;//s->t, 权值c
    int type;
    cin>>n>>m;
    for(int i=0; i<m; i++)
    {
        cin>>type>>s>>t>>c;
        if(type==1)
            c=c*c;
        graph[s].push_back(Edge(t,c));
        graph[t].push_back(Edge(s,c));
    }
    dij(1,n);
    cout<<dist[n]<<endl;

}
/** \brief
输入样例
6 8
0 1 6 100
0 1 5 30
0 1 3 10
0 2 3 5
0 3 4 50
0 4 6 10
0 5 4 20
0 5 6 60
 */

