/*
	50�ְ汾
	����ģ�ⷨ
	����ƭһ����� 
*/
#include<iostream>
#define MAXN 100001
using namespace std;
int n,m; 
int a[MAXN]={0};
int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	int opt,l,r,v;
	while(m--)
	{
		cin>>opt;
		if(opt==1)
		{
			cin>>l>>r>>v;
			for(int i=l;i<=r;i++)
			{
				if(a[i]>=v && a[i]%v==0)
					a[i]/=v;
			}
		}
		else
		{
			unsigned long long ans = 0;
			cin>>l>>r;
			for(int i=l;i<=r;i++)
				ans+=a[i];
			cout<<ans<<endl;
		}
	}
}


