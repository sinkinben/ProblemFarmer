#include<bits/stdc++.h>
using namespace std;
bool pos[1001]={0};
bool neg[1001]={0};
int main()
{
	int n;
	int t;
	cin>>n;
	cin.ignore();
	for(int i=0;i<n;i++)
	{
		cin>>t;
		if(t>0)
			pos[t]=true;
		else
			neg[-t]=true;	
	}
	int ans=0;
	for(int i=1;i<=1000;i++)
		ans+=(pos[i]&&neg[i]);
	cout<<ans<<endl;
	return 0;
}

