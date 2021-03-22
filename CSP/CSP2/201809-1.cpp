#include<bits/stdc++.h>
using namespace std;
int price[1000]={0}; 
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>price[i];
	cout<<(price[0]+price[1])/2<<' ';
	for(int i=1;i<=n-2;i++)
		cout<<(price[i-1]+price[i]+price[i+1])/3<<' ';
	cout<<(price[n-2]+price[n-1])/2<<endl;
}

