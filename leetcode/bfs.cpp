#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
using namespace std;
map<int, vector<int>> graph;
int n, m;
void bfs(int start)
{
    bool vis[n];
    memset(vis, 0, sizeof(bool) * n);
    queue<int> q;
    q.push(start);
    vis[start]=1;
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        cout<<x<<' ';
        for(int v:graph[x])
        {
            if (!vis[v])
            {
                vis[v]=1;
                q.push(v);
            }
        }
    }

}
int main()
{
    cin >> n >> m;
    int a, b;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for (auto it = graph.begin(); it!=graph.end(); it++)
    {
        cout<<it->first<<':';
        for (int x:it->second)
        {
            cout<<x<<" ";
        }
        cout<<endl;
    }
    for (int i = 0; i < n; i++)
    {
        bfs(i);
        cout<<endl;
    }
}
/*
4 4 
0 1
0 2
1 3
2 3
 */
