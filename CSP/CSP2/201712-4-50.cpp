/*
	50分答案
	对于权值的处理：t=1,则存入c^2; t=0, 则存入c 
*/
#include<bits/stdc++.h>
#define VNUM	500
using namespace std;
struct Box{
	int adjVex=-1;
	int cost=INT_MAX;
	bool isAdded=false;
};
int vnum=0;
int nume=0;
int a[VNUM][VNUM]={{0}};
Box box[VNUM];
void init()
{ 
	cin>>vnum>>nume;
	int tt,aa,bb,cc;
	for(int i=0;i<vnum;i++)
		for(int j=0;j<vnum;j++)
			a[i][j]=INT_MAX;
	for(int i=0;i<nume;i++)
	{
		cin>>tt>>aa>>bb>>cc;
		if(tt==1)
			cc=cc*cc;
		aa--, bb--;
		a[aa][bb]=a[bb][aa]=cc;
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
	cout<<box[vnum-1].cost<<endl;
}
int main()
{
	init();
	dijkstra(0);
}


