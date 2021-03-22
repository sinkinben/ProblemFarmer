#include<bits/stdc++.h>
using namespace std;
struct S{
	int num=0;
	int times=0;
};
bool cmp(S s1, S s2)
{
	if(s1.times > s2.times || (s1.times == s2.times && s1.num < s2.num))	
		return true;
	return false;
}
int h[1001]={0};
int n=0;
int main()
{
	cin>>n;
	int t;
	for(int i=0;i<n;i++)
	{
		cin>>t;
		h[t]++;
	}
	
	S s;
	vector<S> v;
	for(int i=0;i<1001;i++)
	{
		if(h[i])
		{
			s.num=i;
			s.times=h[i];
			v.push_back(s); 
		}
	}
	sort(v.begin(),v.end(),cmp);
	for(int i=0;i<v.size();i++)
		cout<<v[i].num<<" "<<v[i].times<<endl;
	return 0;
}
