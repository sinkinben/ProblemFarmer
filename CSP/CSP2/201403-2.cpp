#include<bits/stdc++.h>
using namespace std;
struct Win{
	int x1=-1,y1=-1,x2=-1,y2=-1;
	int order=-1;
	bool isClicked(int x, int y)
	{
		return (x1<=x && x<=x2) && (y1<=y && y<=y2);
	}
};
Win win[11];
int m,n;
void move2bottom(int index)
{
	Win t = win[index];
	for(int i=index;i<n;i++)
		win[i]=win[i+1];
	win[n]=t;
}
int main()
{
	cin>>n>>m;
	cin.ignore();
	for(int i=1;i<=n;i++)
	{
		win[i].order=i;
		cin>>win[i].x1>>win[i].y1>>win[i].x2>>win[i].y2;
		cin.ignore();
	}
	int x,y;
	for(int i=0;i<m;i++)
	{
		cin>>x>>y;
		cin.ignore();
		bool flag=false;
		for(int j=n;j>=1;j--)
		{
			if(win[j].isClicked(x,y))
			{
				flag=true;
				cout<<win[j].order<<endl;
				move2bottom(j);
				break;
			}
		}
		if(!flag)
			cout<<"IGNORED"<<endl;
		
	}
}

