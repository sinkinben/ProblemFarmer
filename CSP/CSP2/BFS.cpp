#include<iostream>
#include<vector>
#include<queue>
#define MAX_N	100
#define MAX_M 	100
using namespace std;
int n,m;//点数，边数 
vector<int> edge[MAX_N];//图的邻接链表 
void BFS(int start)
{
	queue<int> q;
	bool vis[MAX_N]={0};
	int now;
	q.push(start);
	vis[start]=1;
	//cout<<start<<' ';
	while(!q.empty())
	{
		now=q.front();
		q.pop();
		for(int x : edge[now])
		{
			if(!vis[x])
			{
				vis[x]=1;
				cout<<x<<' ';
				q.push(x);
			}
		}
	}
	cout<<endl;
}
int main()
{
	//顶点编号1->n 
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=0;i<=n;i++)
		edge[i].clear();
	int a,b;
	for(int i=0;i<m;i++)
	{
		cin>>a>>b;
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	cout<<"Info"<<endl;
	for(int i=1;i<=n;i++)
	{
		cout<<i<<":";
		for(int x:edge[i])
			cout<<x<<' ';
		cout<<endl;
	}
	cout<<"BFS"<<endl;
	for(int i=1;i<=n;i++)
	{
		cout<<i<<": ";
		BFS(i);
	}
}


