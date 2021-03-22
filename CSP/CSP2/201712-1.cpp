#include<iostream>
using namespace std;
int n;
int a[1001]={0};
int main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	int gap=INT_MAX;
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			gap=min(gap,abs(a[i]-a[j]));
		}
	}
	cout<<gap<<endl;
}


