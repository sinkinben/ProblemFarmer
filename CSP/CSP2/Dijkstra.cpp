#include<bits/stdc++.h>
/*
input: 点数+矩阵
顶点标号从0开始 
测试样例
6
0 0 10 0  30 100
0 0 5  0  0  0
0 0 0  50 0  0
0 0 0  0  0  10
0 0 0  20 0  60
0 0 0  0  0  0 


input:点数+边数+边
6 8
0 2 10
0 4 30
0 5 100
1 2 5
2 3 50
3 5 10
4 3 20
4 5 60 
*/ 
using namespace std;
struct Box{
	int adjVex=-1;
	int cost=INT_MAX;
	bool isAdded=false;
};
int vnum=0;
int a[100][100]={{0}};
Box box[200+1];
void init()
{ 
	cin>>vnum;
	for(int i=0;i<vnum;i++)
	{
		for(int j=0;j<vnum;j++)
		{
			cin>>a[i][j];
			if(a[i][j]==0)
				a[i][j]=INT_MAX;
		}
	}
}
void floyd()
{
	for(int i=0;i<vnum;i++)
	{
		for(int j=0;j<vnum;j++)
		{
			for(int k=0;k<vnum;k++)
			{
				if(a[j][i]!=INT_MAX && a[i][k]!=INT_MAX && a[j][k] > a[j][i] + a[i][k])
					a[j][k] = a[j][i] + a[i][k];
			}
		}
	}
	
	for(int i=0;i<vnum;i++)
	{
		for(int j=0;j<vnum;j++)
		{
			if(a[i][j]!=INT_MAX)
				cout<<setw(4)<<a[i][j];
			else
				cout<<setw(4)<<'*';
		}
		cout<<endl;
	}
}

void dijkstra(int start)
{
	for(int i=0;i<vnum;i++)
	{
		if(a[start][i]!=INT_MAX)
		{
			box[i].adjVex=start;
			box[i].cost=a[start][i];
		}
	}
	box[start].isAdded=true;
	for(int i=0;i<vnum-1;i++)
	{
		int minIndex=vnum;
		for(int k=0;k<vnum;k++)
		{
			if(!box[k].isAdded && box[k].cost < box[minIndex].cost)
				minIndex=k;
		}
		box[minIndex].isAdded=true;
		
		for(int k=0;k<vnum;k++)
		{
			if(!box[k].isAdded && a[minIndex][k]!=INT_MAX && box[k].cost > a[minIndex][k] + box[minIndex].cost)
			{
				box[k].adjVex=minIndex;
				box[k].cost=a[minIndex][k] + box[minIndex].cost;
			}
		}
	}
	
	for(int i=0;i<vnum;i++)
	{
		if(box[i].cost!=INT_MAX)
			cout<<start<<"->"<<i<<' '<<box[i].cost<<endl; 
	}
}
void printPath(int k)
{
	if(k==0)
		return;
	else
	{
		printPath(box[k].adjVex);
		cout<<"->"<<k; 
	}
}
int main()
{
	init();
	floyd();
	init();
	dijkstra(0);
	for(int i=0;i<vnum;i++)
		printf("0"), printPath(i), printf("\n"); 
}


