#include<iostream>
using namespace std;
int m,n,p,q;
void move(int *a, int id,int mov)
{
	int pos=-1;
	for(int i=0;i<n;i++)
	{
		if(a[i]==id)
		{
			pos=i;
			break;
		}
	}
	if(mov>0)
	{
		int i;
		for(i=pos;i<=pos+mov-1;i++)
			a[i]=a[i+1];
		a[i]=id;
	}
	else
	{
		int i;
		for(i=pos;i>=pos+mov+1;i--)
			a[i]=a[i-1];
		a[i]=id;
	}
	
}
int main()
{
	cin>>n>>m;
	int a[n];
	for(int i=0;i<n;i++)
		a[i]=i+1;
	while(m--)
	{
		cin>>p>>q;
		move(a,p,q);
	}
	for(int i=0;i<n;i++)
		cout<<a[i]<<' ';
	 
}


