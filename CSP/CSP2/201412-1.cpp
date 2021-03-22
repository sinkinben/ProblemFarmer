#include<iostream>
using namespace std;
int a[1001]={0};
int main()
{
	int n;
	cin>>n;
	int t;
	while(n--)
	{
		cin>>t;
		a[t]++;
		cout<<a[t]<<' ';
	}
}


