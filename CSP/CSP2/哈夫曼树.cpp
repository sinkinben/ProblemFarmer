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
	cin>>n;	//�ж��ٸ�����Ҷ�ӽڵ㣩 
	while(n--)
	{
		cin>>x;
		q.push(x);
	}
	while(q.size()>1)
	{
		//ȡ��С��2��Ҷ�� 
		a = q.top(), q.pop();
		b = q.top(), q.pop();
		ans+=a+b;
		q.push(a+b); 
	}
	cout<<ans<<endl;
	
}


