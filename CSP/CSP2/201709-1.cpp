#include<iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int ans=0;
	while(n)
	{
		if(n>=50)
			n-=50,ans+=7;
		else if(n>=30)
			n-=30,ans+=4;
		else
			n-=10,ans++;
	}
	cout<<ans<<endl;
}


