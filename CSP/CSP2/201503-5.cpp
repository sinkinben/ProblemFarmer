/*
    0�ְ汾
    sad = =
    ˼·������dij���s��t�����·��
    Ȼ��s->t���ҳ�w��С�ĳ���k
    k->t��ʳ�ﶼ��k����,������ret
    Ȼ��ݹ����calc(s,k)
    s->t�Ļ�������ret+calc(s,k)

    ��ʱ�벻������
*/
#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
#include<cstdio>
#include<cassert>
#define MAXMN 100001
#define VNUM MAXMN
#define ENUM MAXMN
typedef unsigned long long ull;
struct Edge{
    int u,v,cost;
    Edge(int uu=-1, int vv=-1, int cc=-1):u(uu),v(vv),cost(cc){}
};
struct qnode{
    int v,cost;
    qnode(int vv=0, int cc=0):v(vv),cost(cc){}
    bool operator < (const qnode &node) const {return cost > node.cost;}
};
using namespace std;
int n,m;
int w[MAXMN]={0};

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
        addEdge(v,u,c);
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
void path(int k, vector<int> &v)
{
    if(k==-1)
        return;
    else
    {
        path(_prev[k],v);
        v.push_back(k);
    }
}
int getCost(int u, int v)
{
    for(int i=0;i<n;i++)
    {
        int k=head[i];
        while(k!=-1)
        {
            //edge[k].print();
            if(edge[k].u==u && edge[k].v==v)
                return edge[k].cost;
            k=_next[k];
        }
    }
    assert(0);

}
ull calc(vector<int> &v)
{
    int s=v[0];
    int t=v.back();
    if(s==t)
        return 0;
    if(v.size()==2)
        return w[s]*getCost(s,t);
    int minwIndex=v[0];
    int vIndex=0;
    int vsize = v.size();
    for(int i=1;i<vsize-1;i++)
    {
        if(w[v[i]]<w[minwIndex])
            minwIndex=v[i], vIndex=i;
    }
    //cout<<"minwIndex="<<minwIndex<<endl;
    //cout<<"vIndex="<<vIndex<<endl;
    //v[minwIndex] -> v[size-1]�ĳ���
    ull len = 0;
    for(int i=vIndex;i<vsize-1;i++)
        len+=getCost(v[i],v[i+1]);
    ull ret=w[minwIndex]*len;
    //cout<<"ret="<<ret<<endl;
    vector<int> vv(v.begin(),v.begin()+vIndex+1);
//    for(int x:vv)
//        cout<<x<<' ';
//    cout<<endl;
    return ret+calc(vv);
}


int main()
{
    ios::sync_with_stdio(0);
    cin>>n>>m;
    for(int i=0;i<n;i++)
        cin>>w[i];
    init(n,n-1);
    int s,t;
    while(m--)
    {
        cin>>s>>t;
        s--,t--;
        memset(vis,0,sizeof(vis));
        memset(_prev,-1,sizeof(_prev));
        for(int i=0;i<n;i++)
            dist[i]=INF;
        dij(n,s);
        vector<int> v;
        path(t,v);
//        for(int x: v)
//            cout<<x<<' ';
//        cout<<endl;
        cout<<calc(v)<<endl;

    }

}
/*
6 4
1 7 3 2 5 6
1 2 4
1 3 5
2 4 1
3 5 2
3 6 1
2 5
4 6
6 4
5 6


35
16
26
13
*/


