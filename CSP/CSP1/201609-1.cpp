#include<bits/stdc++.h>
using namespace std;
int n;
int a[1000]={0};
int main()
{
	cin>>n;
	int gap=INT_MIN;
	cin>>a[0];
	for(int i=1;i<n;i++)
	{
		cin>>a[i];
		gap=max(gap,abs(a[i]-a[i-1]));
	}
	cout<<gap<<endl;
	return 0;
}
