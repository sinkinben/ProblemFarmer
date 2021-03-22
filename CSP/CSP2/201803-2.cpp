#include<iostream>
#include<algorithm>
#define RIGHT true
#define LEFT false
#define revdir(dir) ((dir)=!(dir))
using namespace std;
struct Ball{
	int id=0;
	int pos=-1;
	bool dir=RIGHT;
};
int n,L,t;
Ball ball[101];
bool cmp_id(Ball b1, Ball b2)
{
	return b1.id<b2.id;
}
bool cmp_pos(Ball b1, Ball b2)
{
	return b1.pos<b2.pos;
}
int main()
{
	cin>>n>>L>>t;
	for(int i=1;i<=n;i++)
	{
		ball[i].id=i;
		cin>>ball[i].pos; 
	}
	sort(ball+1, ball+n+1, cmp_pos);
	while(t--)
	{
		for(int i=1;i<=n;i++)
		{
			if(ball[i].dir == RIGHT)
				ball[i].pos++;
			else
				ball[i].pos--;
		}
		if(ball[1].pos==0)
			ball[1].dir=RIGHT;
		for(int i=1;i<=n-1;i++)
		{
			if(ball[i].pos == ball[i+1].pos)
				revdir(ball[i].dir), revdir(ball[i+1].dir), i++;
		}
		if(ball[n].pos==L)
			ball[n].dir=LEFT;
	}
	sort(ball+1,ball+n+1,cmp_id);
	for(int i=1;i<=n;i++)
		cout<<ball[i].pos<<' ';
}

