#include<bits/stdc++.h>
using namespace std;
int n=0,m=0,r=0,k=0;
struct Point{
	int x=-1,y=-1;
};
bool graph[201][201]={{0}};
Point pos[201];

inline bool isLinked(Point &p1, Point &p2)
{
	return sqrt(pow((p1.x-p2.x),2)+pow((p1.y-p2.y),2))<=(float)r;
}
int first(int u)	//u的第一个相邻 
{
	assert(u!=-1);
	for(int i=1;i<=m+n;i++)
	{
		if(graph[u][i]==1)
			return i;
	}
	return -1;
}

int next(int u, int w)
{
	assert(u!=-1 && w!=-1);
	for(int i=w+1;i<=m+n;i++)
	{
		if(graph[u][i]==1)
			return i;
	}
	return -1;
}

int bfs(int start, int end)
{
	bool isVis[m+n+1];
	memset(isVis,0,sizeof(isVis));
	queue< pair<int,int> > q;
	q.push(make_pair(start,0));
	isVis[start]=1;
	int len=INT_MAX;
	while(!q.empty())
	{
		pair<int,int> p=q.front();
		int u=p.first;
		q.pop();
		int w=first(u);
		while(w!=-1)
		{
			if(!isVis[w])
			{
				isVis[w]=1;
				//cout<<w<<' '<<end<<endl;
				if(w==end)
					len=min(len,p.second);
				else if(p.second<r)
					q.push(make_pair(w,p.second+1));
				else
					break;	
			}
			w=next(u,w);
		}
	}
	return len;
}

int main()
{
	cin>>n>>m>>k>>r;
	cin.ignore();
	for(int i=1;i<=m+n;i++)
		cin>>pos[i].x>>pos[i].y;
	
	for(int i=1;i<m+n;i++)
	{
		for(int j=i+1;j<=m+n;j++)
				graph[i][j]=graph[j][i]=isLinked(pos[i],pos[j]);
	}
	
//	for(int i=1;i<=m+n;i++)
//	{
//		for(int j=1;j<=m+n;j++)
//			cout<<graph[i][j]<<' ';
//		cout<<endl;
//	}
	
	cout<<bfs(1,2);
	
	
}
