#include<bits/stdc++.h>
// red -> green -> yellow 
using namespace std;
int r,y,g;
int n;
int main()
{
	ios::sync_with_stdio(0);
	int ans=0;
	cin>>r>>y>>g;
	cin>>n;
	int k,t;
	while(n--)
	{
		cin>>k>>t;
		if(k==0 || k==1)
			ans+=t;
		else if(k==2)
			ans+=t+r;
	}
	cout<<ans<<endl;
	
	
}

