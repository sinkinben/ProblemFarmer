#include<bits/stdc++.h>
using namespace std;
struct Win{
	int order;
	int x1,y1,x2,y2;
	Win()
	{
		order=x1=y1=x2=y2=-1;
	}
};
int n=0,m=0;
Win win[10];
//win[9]ÊÇ×î¶¥²ã 
inline bool isClicked(int x, int y, Win &w)
{
	return (w.x1<=x&&x<=w.x2)&&(w.y1<=y&&y<=w.y2);
}

void move(int order)
{
	Win w=win[order];
	for(int i=order;i<=n-2;i++)
		win[i]=win[i+1];
	win[n-1]=w;
}

int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		win[i].order=i;
		cin>>win[i].x1>>win[i].y1>>win[i].x2>>win[i].y2;
	}
	int x,y;
	while(m)
	{
		cin>>x>>y;
		m--;
		bool flag=false;
		for(int i=n-1;i>=0;i--)
		{
			if(isClicked(x,y,win[i]))
			{
				cout<<win[i].order+1<<endl;
				move(i);
				flag=true;
				break;
			}	
		}
		if(flag==false)
			cout<<"IGNORED"<<endl;
	}
	return 0;
}
