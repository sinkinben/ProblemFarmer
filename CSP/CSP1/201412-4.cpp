#include<bits/stdc++.h>
using namespace std;
int n,m;
bool field[1001][1001]={{0}};
int weight[1001][1001]={{0}};
struct Box{
	int adjVex=-1;
	int weight=INT_MAX;
};
void prim(int start)
{
	Box box[n+1];
	bool add[n+1];
	memset(add,0,sizeof(add));
	add[start]=true;
	for(int i=1;i<=n;i++)
	{
		if(field[start][i])
		{
			box[i].adjVex=start;
			box[i].weight=weight[start][i];
		} 
	}
	for(int k=0;k<=n-1;k++)
	{
		int minIndex=0;
		for(int i=1;i<=n;i++)
		{
			if(!add[i]&&box[i].adjVex!=-1 && box[i].weight < box[minIndex].weight)
				minIndex=i;
		}
		//cout<<minIndex<<endl;
		add[minIndex]=true;
		for(int i=1;i<=n;i++)
		{
			if(!add[i] && field[minIndex][i] && weight[minIndex][i] < box[i].weight)
			{
				box[i].weight=weight[minIndex][i];
				box[i].adjVex=minIndex;
			}
		}
	}
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		if(box[i].weight!=INT_MAX)
			sum+=box[i].weight;
	}
	cout<<sum<<endl;
}

int main()
{
	cin>>n>>m;
	cin.ignore();
	int a,b,c;
	for(int i=0;i<m;i++)
	{
		cin>>a>>b>>c;
		cin.ignore();
		field[a][b]=field[b][a]=true;
		weight[a][b]=weight[b][a]=c;
	}
	prim(2);
	
}
