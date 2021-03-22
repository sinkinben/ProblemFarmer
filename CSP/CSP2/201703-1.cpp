#include<iostream>
using namespace std;
int a[1001]={0};
int main()
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	
	int m=0;
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		m+=a[i];
		if(m>=k)
			ans++, m=0;
	}
	ans+=(m!=0);
	cout<<ans<<endl;
}


