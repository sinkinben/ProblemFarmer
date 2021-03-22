#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#define VMAX 500002
#define EMAX 100002
struct Edge{
    int u,v,c;
    Edge(int uu=-1, int vv=-1, int cc=-1)
    :u(uu),v(vv),c(cc){}
    bool operator < (const Edge &e) {return c<e.c;}
};
using namespace std;
int n,m,root;
int tree[VMAX];
Edge edge[EMAX];

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
	cin>>n>>m>>root;
	for(int i=1;i<=m;i++)
        cin>>edge[i].u>>edge[i].v>>edge[i].c;
    sort(edge+1, edge+1+m);
    memset(tree,-1,(n+5)*sizeof(int));

    int a,b;
    int ans=INT_MIN;
    for(int i=1;i<=m;i++)
    {
        a=findRoot(edge[i].u);
        b=findRoot(edge[i].v);
        if(a!=b)
            tree[a]=b, ans=max(ans,edge[i].c);
    }
    cout<<ans<<endl;
}


