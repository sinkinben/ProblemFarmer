#include<bits/stdc++.h>
#define rev(a) ((a)=!(a))
using namespace std;
int n=0,l=0,t=0;
int a[100]={0};
struct Ball{
	int id=INT_MAX;
	int pos=0;
	bool right=true;
};
Ball ball[100];
bool cmpPos(Ball b1, Ball b2)
{
	return b1.pos<b2.pos;
}

bool cmpId(Ball b1, Ball b2)
{
	return b1.id<b2.id;
}
void exec()
{
	for(int i=0;i<n;i++)
	{
		if(ball[i].right)
			ball[i].pos++;
		else
			ball[i].pos--;
	}
	if(ball[0].pos==0&&ball[0].right==false)
		ball[0].right=true;
	for(int i=1;i<=n-1;i++)
	{
		if((ball[i].pos==ball[i-1].pos))
			rev(ball[i].right), rev(ball[i-1].right), i++;
	}
	if(ball[n-1].pos==l && ball[n-1].right==true)
		ball[n-1].right=false;
}

int main()
{
	cin>>n>>l>>t;
	for(int i=0;i<n;i++)
	{
		ball[i].id=i;
		cin>>ball[i].pos;
	}
	sort(ball,ball+n,cmpPos);
	while(t)
	{
		t--;
		exec();
	}
	sort(ball,ball+n,cmpId);
	for(int i=0;i<n;i++)
		cout<<ball[i].pos<<' ';
	return 0;
}
