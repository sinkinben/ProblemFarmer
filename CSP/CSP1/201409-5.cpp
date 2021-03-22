#include<bits/stdc++.h>

using namespace std;
int n,m;

int main()
{
	cin>>n>>m;
	if(n==1 || n==2 || (n*m%6))
	{
		cout<<0<<endl;
		return 0;
	}
	unsigned int N=n/3;
	unsigned int M=m/2;
	unsigned int K=N*M; 
//	long long int ans=pow(2,M)%(1000000007);
//	ans=pow(ans,N)%(1000000007);
//	cout<<ans<<endl; 
	unsigned long long ans=1;
	while(K)
	{
		K--;
		ans=(ans<<1)%1000000007;
	}
	cout<<ans<<endl;
	
}
