#include<bits/stdc++.h>
using namespace std;
int a[1000]={0};
int n=0;
int main()
{
	int count=1;
	cin>>n;
	cin>>a[0];
	for(int i=1;i<n;i++)
	{
		cin>>a[i];
		if(a[i]!=a[i-1])
			count++;
	}
	cout<<count<<endl;
	return 0;
}
