#include<bits/stdc++.h>
using namespace std;
// red  -> green  -> yellow
// [0,r)-> [r,r+g)-> [r+g,r+g+y)
/*
	ans和point要用long long
	int会溢出导致错误 
*/
int r,g,y;
int main()
{
	cin>>r>>y>>g;
	cin.ignore();
	int n;
	cin>>n;
	int k,t;
	long long ans=0;
	long long point;
	while(n--)
	{
		cin>>k>>t;
		if(k==0)
		{
			ans+=t;
			continue;
		}
		else if(k==1)
			point=r-t;
		else if(k==2)
			point=(r+g+y-t);
		else if(k==3)
			point=(r+g-t);
		
		point=(point+ans)%(r+g+y);
		if(0<=point && point<r)
			ans+=(r-point);
		else if(r+g<=point && point<r+g+y)
			ans+=(r+g+y-point)+r;
	}
	cout<<ans<<endl;
}

