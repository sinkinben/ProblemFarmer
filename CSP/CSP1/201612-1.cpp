#include<iostream>
using namespace std;
int n=0;
int a[1000]={0};
int h[1001]={0};
int sum(int start, int end)
{
	int n=0;
	for(int i=start;i<=end;i++)
		n+=h[i];
	return n;
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		h[a[i]]++;
	}
	
	int ans=-1;
	for(int i=1;i<=1000;i++)
	{
		if(h[i] && sum(0,i-1) == sum(i+1,1000))
		{
			ans=i;
			break;
		}
	}	
	cout<<ans<<endl;
	return 0;
	
	
}
