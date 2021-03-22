/*
    先来一次擅长的BFS做一次
    暴力BFS
    50分版本
    题解说用tarjan
*/
#include<iostream>
#include<cstring>
#include<vector>
#include<set>
#include<queue>
#define MAXN 10001
#define MAXM 100001
using namespace std;
int n,m;
bool vis[MAXN]={0};
bool isTested[MAXN]={0};
vector<int> edge[MAXN];
set<int> reach[MAXN];
void bfs(int start)
{
    queue<int> q;
    int now;
    q.push(start);
    vis[start]=1;
    //cout<<start<<" ";
    while(!q.empty())
    {
        now=q.front();
        q.pop();
        for(int x:edge[now])
        {
            if(!vis[x])
            {
                vis[x]=1;
                //cout<<x<<' ';
                reach[start].insert(x);
                q.push(x);
            }
        }
    }
    //cout<<endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin>>n>>m;
    int a,b;
    while(m--)
    {
        cin>>a>>b;
        edge[a].push_back(b);
    }
    for(int i=1;i<=n;i++)
    {
        bfs(i);
        memset(vis,0,n+5);
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            if(reach[j].find(i)!=reach[j].end() && reach[i].find(j)!=reach[i].end())
                ans++;
        }
    }
    cout<<ans<<endl;


    return 0;
}
