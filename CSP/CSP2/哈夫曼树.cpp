#include<iostream>
#include<queue>
#include<vector>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	int n;
	priority_queue<int,vector<int>,greater<int>> q;
	int x,ans=0;
	int a,b;
	cin>>n;	//有多少个数（叶子节点） 
	while(n--)
	{
		cin>>x;
		q.push(x);
	}
	while(q.size()>1)
	{
		//取最小的2个叶子 
		a = q.top(), q.pop();
		b = q.top(), q.pop();
		ans+=a+b;
		q.push(a+b); 
	}
	cout<<ans<<endl;
	
}


