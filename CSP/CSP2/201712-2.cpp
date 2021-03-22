#include<iostream>
#include<vector>
using namespace std;
int n,k;
int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>k;
	vector<int> v(n);
	for(int i=0;i<n;i++)
		v[i]=i+1;
	int cur=0;
	int index=-1;
	while(v.size()>1)
	{
		cur=cur+1;
		index=(index+1)%v.size();
		if(cur%10==k || (cur>=k && cur%k==0))
		{
			v.erase(v.begin()+index);
			index--;
			if(index==-1)
				index=v.size()-1;
		}		
	}
	cout<<v[0];
}


