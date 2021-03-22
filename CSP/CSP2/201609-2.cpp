#include<iostream>
#include<assert.h>
using namespace std;
int n;
int surplus[20]={0};
bool seat[20][5]={0};

int searchRow(int num)
{
	for(int i=0;i<20;i++)
	{
		if(surplus[i]>=num)
			return i;
	}
	return -1;
}

int main()
{
	for(int i=0;i<20;i++)
		surplus[i]=5;
	int p;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>p;
		int row=searchRow(p);
		if(row!=-1)
		{
			surplus[row]-=p;
			for(int i=0;i<5;i++)
			{
				if(!seat[row][i])
				{
					cout<<(row*5+i+1)<<' ';
					seat[row][i]=true;
					p--;
					if(p==0)
						break;
				}
			}
			assert(surplus[row]>=0);
		}
		else
		{
			for(int i=0;i<20;i++)
			{
				for(int j=0;j<5;j++)
				{
					if(!seat[i][j])
					{
						seat[i][j]=true;
						surplus[i]--;
						cout<<(i*5+j+1)<<' ';
						p--;
						if(p==0)
							break;
					}
				}
				if(p==0)
					break;
			}
		}
		cout<<endl;
	}
}


