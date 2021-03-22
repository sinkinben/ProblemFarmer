//������0��n-1
//_prev[]��¼����·���ڵ��ǰ��
#include<queue>
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<iomanip>
#define ENUM 100
#define VNUM 100
using namespace std;
struct Edge{
    int u,v;
    int cost;
    Edge(int uu=-1,int vv=-1, int cc=-1)
:u(uu),v(vv),cost(cc){}
    void print()
{cout<<u<<" "<<v<<" "<<cost<<endl;}
};

struct qnode{
    int v,cost;
    qnode(int vv=0, int cc=0)
:v(vv),cost(cc){}
bool operator < (const qnode &node) const {return cost > node.cost;}
};
const int INF=0x3f3f3f3f;

Edge edge[ENUM];
int dist[ENUM];//dist[i]��src��i�����·
int e=0;//����ı����±�
int head[VNUM], _next[ENUM];//��¼ͼ
int _prev[VNUM];//��ӡ·��
bool vis[VNUM];

inline void addEdge(int u, int v, int c)
{
    edge[e]=Edge(u,v,c);
    _next[e]=head[u];
    head[u]=e;
    e++;
    //ֻ���ǵ����
    //����0->n-1
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
        u--,v--;    //����������ݴ�1��ʼ���
        addEdge(u,v,c);
		addEdge(v,u,c);//���������ͼ
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
    pre=src;
    for(i=1;i<n;i++)
    {
        for(j=head[pre];j!=-1;j=_next[j])
        {
            k=edge[j].v;
            if(!vis[k] && dist[pre]+edge[j].cost<dist[k])
            {
                dist[k]=dist[pre]+edge[j].cost;
                que.push(qnode(edge[j].v,dist[k]));
                _prev[k]=pre;
            }
        }
        while(!que.empty() && vis[que.top().v])
            que.pop();
        if(que.empty())
            break;
        mv=que.top();
        que.pop();
        vis[pre=mv.v]=1;
    }
}
void path(int k)
{
    if(k==-1)
        return;
    else
    {
        path(_prev[k]);
        cout<<"->"<<k;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    int nv, ne;
    cin>>nv>>ne;
    init(nv,ne);

    dij(nv,0);
    for(int i=0;i<nv;i++)
        cout<<dist[i]<<' ';
    cout<<endl;
    //dist[i]Ϊsrc��i�Ķ̾���

    for(int i=0;i<nv;i++)
    {
        path(i);
        cout<<endl;
    }
    cout<<endl;

    //����ͼ
    for(int i=0;i<nv;i++)
    {
        int k=head[i];
        while(k!=-1)
        {
            edge[k].print();
            k=_next[k];
        }
    }

}

/*
������1��ʼ
��������
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

