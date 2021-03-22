#include<bits/stdc++.h>
using namespace std;
int n=0;
int k=0;
int ans=0; 
int weight[1000]={0};
int main()
{
	cin>>n>>k;
	for(int i=0;i<n;i++)
		cin>>weight[i];
	
	int start=0;
	int i=0;
	while(start<n)
	{
		int sum=0;
		for(i=start;i<n;i++)
		{
			sum+=weight[i];
			if(sum>=k)
				break;
		}
		start=i+1;
		ans++;
	}
	cout<<ans<<endl;
	return 0; 
}
