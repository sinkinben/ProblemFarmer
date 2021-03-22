#include<bits/stdc++.h>
using namespace std;
//第r个数是v[r-1] 
int n,m;
inline void op1(vector<int> &V,int l,int r, int v)
{
	if(v==1)
		return;
	for(int i=l-1;i<r;i++)
	{
		if(V[i]%v==0)
			V[i]/=v;
	}
}
inline int op2(vector<int> &V,int l,int r)
{
	int n=0;
	for(int i=l-1;i<r;i++)
		n+=V[i];
	return n;
}

int main()
{
	 cin>>n>>m;
	 cin.ignore();
	 vector<int> V(n);
	 for(int i=0;i<n;i++)
	 	scanf("%d",&V[i]);
	int l,r,v;
	int opt;
	for(int i=0;i<m;i++)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d %d %d",&l,&r,&v);
			op1(V,l,r,v);
		}
		else
		{
			scanf("%d %d",&l,&r);
			printf("%d\n",op2(V,l,r));
		}
	}
	return 0;
} 
