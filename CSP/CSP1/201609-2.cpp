#include<bits/stdc++.h>
#define getOrder(i,j)	(i*5+j+1)
using namespace std;
bool seat[20][5];
int remain[20];
int n;
int p;
int main()
{
	memset(seat,0,sizeof(seat));
	for(int i=0;i<20;i++)
		remain[i]=5;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>p;
		int j=0;
		for(j=0;j<20;j++)
		{
			if(remain[j]>=p)
				break;
		}
		
		if(j<20)	//Ä³Ò»ÐÐ×ùÎ»×ã¹» 
		{ 
			remain[j]-=p;
			for(int k=0;k<5;k++)
			{
				if(seat[j][k]==false&&p)
				{
					seat[j][k]=true;
					p--;
					cout<<getOrder(j,k)<<' '; 
				}
			}
			cout<<endl;
		}
		else
		{
			for(int x=0;x<20;x++)
			{
				for(int y=0;y<5;y++)
				{
					if(seat[x][y]==false && p)
					{
						seat[x][y]=true;
						remain[x]--;
						p--;
						cout<<getOrder(x,y)<<' ';
					}
				}
			}
			cout<<endl;
		}
	}
}
