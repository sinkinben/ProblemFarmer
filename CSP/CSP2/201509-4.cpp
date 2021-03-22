/*==================================================*\
| Tarjanǿ��ͨ����
| CALL: for(i=0; i<n; ++i) if(-1==pre[i]) tarjan(i, n);
\*==================================================*/
/*
tarjan�㷨ģ��
�����ϵ��㷨ģ��
100�ְ汾
*/
#include<iostream>
#include<vector>
#include<cstring>
#define VMAX 10001
#define V VMAX
using namespace std;
vector<int> vec[V];
int id[V], dfn[V], low[V], STACK[V], top=0, _count=0, componentNum=0;
//id[i]��ʾ��i�������ڵ���ͨ������id
int n,m;//����������

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
    int num=0;//��������ķ����ĵ�ĸ���
    do
    {
        num++;
        t = STACK[--top];
        id[t] = componentNum;
        low[t] = n;
    }
    while(t != v);
    ++componentNum; // ǿ��ͨ�����ĸ���
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
        a--,b--;//������붥���1��ʼ���
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
