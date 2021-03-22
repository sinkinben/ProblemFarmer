/** 100分版本
 *  海岛Blog真大神！
 */
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#define VMAX 10005
struct Edge{
    int vex,cost;
    Edge(int vv=-1, int cc=-1):vex(vv),cost(cc){}
};
struct Node{
    int u,cost;
    Node(int uu=-1, int cc=-1):u(uu),cost(cc){}
    bool operator < (const Node &n) const
    { return cost>n.cost;}
};
using namespace std;
vector<Edge> graph[VMAX];
priority_queue<Node> q;
int dist[VMAX]={0};//dist[i]是start到i的最短距离
bool vis[VMAX]={0};//记录是否被访问
int prevex[VMAX]={0};//记录路径的前驱
int toicost[VMAX]={0};//cost[i]表示到达i节点，修建的铁路的cost
void dij(int start, int vnum)
{
    memset(prevex,-1,sizeof(prevex));
    memset(vis,0,sizeof(vis));
    for(int i=0;i<=vnum;i++)
    {
        dist[i]=INT_MAX;
        toicost[i]=INT_MAX;
    }
    dist[start]=0;
    toicost[start]=0;
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
            for(int i=0;i<len;i++)
            {
                int v=graph[u][i].vex;
                int tempcost=graph[u][i].cost;
                int nextdist=dist[u]+tempcost;
                if(vis[v])
                    continue;
                if(dist[v] > nextdist)
                {
                    toicost[v]=tempcost;    //u->v的cost
                    dist[v]=nextdist;
                    q.push(Node(v,nextdist));
                    prevex[v]=u;
                }
                else if(dist[v] == nextdist && toicost[v]>tempcost)
                {
                    //当多个路径同为最短，选择toicost[v]<tempcost的
                    toicost[v]=tempcost;
                    //q.push(Node(v,nextdist));
                    prevex[v]=u;
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
    int s,t,c;//s->t, 权值c
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        cin>>s>>t>>c;
        //双向边
        graph[s].push_back(Edge(t,c));
        graph[t].push_back(Edge(s,c));
    }
    dij(1,n);
    int ans=0;
    for(int i=2;i<=n;i++)
        ans+=toicost[i];
    cout<<ans<<endl;
}
/*
顶点编号1开始
输入样例
6 8
1 6 100
1 5 30
1 3 10
2 3 5
3 4 50
4 6 10
5 4 20
5 6 60
*/

