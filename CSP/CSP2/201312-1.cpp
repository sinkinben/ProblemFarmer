#include<bits/stdc++.h>
using namespace std;
int hash[10001]={0};
int n=0;
int main()
{
	int s;
	cin>>n;
	cin.ignore();
	for(int i=0;i<n;i++)
	{
		cin>>s;
		hash[s]++;
	}
	int index=1;
	for(int i=2;i<=10000;i++)
	{
		if(hash[i]>hash[index])
			index=i;
	}
	cout<<index<<endl;
	return 0;
}
