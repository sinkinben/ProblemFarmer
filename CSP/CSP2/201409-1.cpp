#include<bits/stdc++.h>
#include<iostream> 
using namespace std;
/*
��������������ֿ����ظ������
ԭ���ǡ�������ͬ�����֡� 
*/
int num[10001]={0};
int n=0; 
int main()
{
	cin>>n;
	cin.ignore();
	int t;
	for(int i=0;i<n;i++)
	{
		cin>>t;
		cin.ignore();
		num[t]++;
	}
	int ans=0;
	for(int i=0;i<=10000-1;i++)
	{
		if(num[i]==0 || num[i+1]==0)
			continue;
		ans+=num[i]+num[i+1]-1;
	}
	cout<<ans<<endl;
}

