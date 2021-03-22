/*********************************
 * 100分版本
 * 看了网上的题解
 * BFS题目
 */

#include<iostream>
#include<cstdio>
#include<queue>
#define MAXMN 105
#define MAXRC MAXMN
#define MAXTIME 10000
using namespace std;
struct DangerTime{
    int start=-1, _end=-1;
};
struct Node{
    int x,y,t;
    Node(int xx=-1, int yy=-1, int tt=-1)
    :x(xx),y(yy),t(tt){}
};


int n,m,t;
DangerTime dt[MAXRC][MAXRC];
bool vis[MAXMN][MAXMN][MAXTIME]={{{0}}};
int main()
{
    ios::sync_with_stdio(0);
    cin>>n>>m>>t;
    int r,c,a,b;
    while(t--)
    {
        cin>>r>>c>>a>>b;
        dt[r][c].start=a;
        dt[r][c]._end=b;
    }
    queue<Node> q;
    int time=0;
    Node now(1,1,0);
    vis[1][1][0]=1;
    q.push(now);
    while(!q.empty())
    {
        now = q.front();
        q.pop();
        if(now.x == n && now.y == m)
        {
            cout<<now.t<<endl;
            break;
        }
        int x=now.x;
        int y=now.y;
        int time=now.t;
        if((x-1)>=1 && !vis[x-1][y][time+1] && (time+1<dt[x-1][y].start || time+1>dt[x-1][y]._end))
        {
            vis[x-1][y][time+1]=1;
            q.push(Node(x-1,y,time+1));
        }
        if((y+1)<=m && !vis[x][y+1][time+1] && (time+1<dt[x][y+1].start || time+1>dt[x][y+1]._end))
        {
            vis[x][y+1][time+1]=1;
            q.push(Node(x,y+1,time+1));
        }
        if((x+1)<=n && !vis[x+1][y][time+1] && (time+1<dt[x+1][y].start || time+1>dt[x+1][y]._end))
        {
            vis[x+1][y][time+1]=1;
            q.push(Node(x+1,y,time+1));
        }
        if((y-1)>=1 && !vis[x][y-1][time+1] && (time+1<dt[x][y-1].start || time+1>dt[x][y-1]._end))
        {
            vis[x][y-1][time+1]=1;
            q.push(Node(x,y-1,time+1));
        }

    }


}

