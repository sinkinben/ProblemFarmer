#include<bits/stdc++.h>
#define out(i)	(i%k==0)||(i%10==k)
using namespace std;
int n=0,k=0;
int main()
{
	cin>>n>>k;
	vector<int> v(n+1);
	for(int i=1;i<=n;i++)
		v[i]=i;
	int i=1;
	int count=1;
	while(v.size()!=2)
	{
		if(out(count))
		{
			v.erase(v.begin()+i);
			i--;
		}
		i++;
		if(i==v.size())
			i=1;
		count++;
	}
	cout<<v[1]<<endl;
}
