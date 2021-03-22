#include<bits/stdc++.h>
using namespace std;
int n;
int a[1000]={0};
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	
	int count=0;
	for(int i=1;i<=n-2;i++)
	{
		if((a[i-1]<a[i]&&a[i]>a[i+1])||(a[i-1]>a[i]&&a[i]<a[i+1]))
			count++;
	}
	cout<<count<<endl;
	return 0;
}
