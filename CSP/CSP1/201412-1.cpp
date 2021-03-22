#include<bits/stdc++.h>
using namespace std;
int a[1001]={0};
int data[1001]={0};
int n;
int main()
{
	cin>>n;
	int t;
	for(int i=1;i<=n;i++)
	{
		cin>>data[i];
		a[data[i]]++;
		cout<<a[data[i]]<<' ';
	}
	return 0;
	
}
