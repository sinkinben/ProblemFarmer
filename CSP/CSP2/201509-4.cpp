/*==================================================*\
| Tarjan强连通分量
| CALL: for(i=0; i<n; ++i) if(-1==pre[i]) tarjan(i, n);
\*==================================================*/
/*
tarjan算法模板
抄网上的算法模板
100分版本
*/
#include<iostream>
#include<vector>
#include<cstring>
#define VMAX 10001
#define V VMAX
using namespace std;
vector<int> vec[V];
int id[V], dfn[V], low[V], STACK[V], top=0, _count=0, componentNum=0;
//id[i]表示第i个点所在的连通分量的id
int n,m;//点数，边数

unsigned int ans=0;

void tarjan(int v, int n)  // vertex: 0 ~ n-1
{
    int t, minc = low[v] = dfn[v] = _count++;
    vector<int>::iterator pv;
    STACK[top++] = v;
    for (pv = vec[v].begin(); pv != vec[v].end(); ++pv)
    {
        if(-1 == dfn[*pv]) tarjan(*pv, n);
        if(low[*pv] < minc) minc=low[*pv];
    }
    if(minc < low[v])
    {
        low[v] = minc;
        return;
    }
    int num=0;//本次求出的分量的点的个数
    do
    {
        num++;
        t = STACK[--top];
        id[t] = componentNum;
        low[t] = n;
    }
    while(t != v);
    ++componentNum; // 强连通分量的个数
    //cout<<"num="<<num<<endl;
    ans+=(num-1)*num/2;
}
void init()
{
    cin>>n>>m;
    int a,b;
    for(int i=0;i<m;i++)
    {
        cin>>a>>b;
        a--,b--;//如果输入顶点从1开始编号
        vec[a].push_back(b);
    }
    memset(dfn,-1,sizeof(dfn));
}
int main()
{
    init();
    for(int i=0; i<n; ++i)
        if(-1==dfn[i])
            tarjan(i, n);
    cout<<ans<<endl;
}
