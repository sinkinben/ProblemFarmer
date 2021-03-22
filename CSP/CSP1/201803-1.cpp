#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	int ans=0;
	int point=0;
	while(cin>>n)
	{
		if(n==1)
			ans++, point=0;
		else if(n==2)
		{
			point+=2;
			ans+=point;
		}
		else
			break;
	}
	cout<<ans<<endl;
	return 0;
} 

