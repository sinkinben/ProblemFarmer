#include<iostream>
#define MAX_M 100001
#define MAX_R 200002
const unsigned long long Q = 998244353; 
using namespace std;
int m,l,r;
unsigned long long k[MAX_M]={0};
unsigned long long a[MAX_R]={1,0};
unsigned long long func(int n, int m)
{
	int limit = min(n,m);
	unsigned long long an=0;
	for(int i=1;i<=limit;i++)
	{
		an+=((unsigned long long)((k[i])*(a[n-i])));
		an=an%Q;
	}
	return an;
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>m>>l>>r;	
	for(int i=1;i<=m;i++)
		cin>>k[i];
	for(int n=1;n<=r;n++)
		a[n]=func(n,m);
	for(int i=l;i<=r;i++)
		cout<<a[i]<<endl;
}


