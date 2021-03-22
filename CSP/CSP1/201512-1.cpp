#include<bits/stdc++.h>
using namespace std;
//0...1000000000
//0...2147483647
int n;
int sum=0;
int main()
{
	cin>>n;
	while(n)
	{
		sum+=n%10;
		n/=10;
	}
	cout<<sum<<endl;
	return 0;
}
