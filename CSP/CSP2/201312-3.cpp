#include<iostream>
#include<algorithm>
#define MAXN 1001
using namespace std;
int n;
int a[MAXN]={0};
int main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
		
	int ans = INT_MIN;
	for(int i=0;i<n;i++)
	{
		int curmax = a[i];
		int minh = a[i];
		for(int j=i+1;j<n;j++)
		{
			minh=min(minh,a[j]);
			curmax=max(curmax,minh*(j-i+1));
		}
		ans=max(ans,curmax);
	}
	cout<<ans<<endl;
}


