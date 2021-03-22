#include<bits/stdc++.h>
using namespace std;
int n=0,m=0;
int a[1000]={0};
//a[i] is id, and i is position
int getIndex(int id)
{
	for(int i=1;i<=n;i++)
		if(id == a[i])
			return i;
}
void move(int index, int mov)
{
	if(mov>0)
	{
		int id=a[index];
		for(int i=index;i<mov+index;i++)
			a[i]=a[i+1];
		a[mov+index]=id;
	}
	else
	{
		int id=a[index];
		for(int i=index;i>index+mov;i--)
		{
			a[i]=a[i-1];
		}
		a[index+mov]=id;
	}
}
int main()
{
	cin>>n;
	cin>>m;
	for(int i=0;i<n;i++)
		a[i+1]=i+1;
	int id,mov;
	for(int i=0;i<m;i++)
	{
		cin>>id>>mov;
		int index=getIndex(id);
		move(index,mov);
	}
	for(int i=1;i<=n;i++)
		cout<<a[i]<<' ';
	
}
