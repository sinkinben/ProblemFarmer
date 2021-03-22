#include<bits/stdc++.h>
using namespace std;
int N=0;
int ans=0;
int main()
{
	cin>>N;
	while(N)
	{
		if(N>=50)
			N-=50, ans+=7; 
		else if(N>=30)
			N-=30, ans+=4;
		else
			N-=10, ans++;		
	}
	cout<<ans<<endl;
}
