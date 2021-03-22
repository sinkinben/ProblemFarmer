#include<iostream>
#include<string.h>
#include<algorithm>
#include<vector>
#define Borrow 2
#define Return 1
using namespace std;
struct Event{
	int key=-1;
	int time=-1;
	int type=-1;
};
int n,k;
int box[20000]={0};
bool cmp(Event e1, Event e2)
{
	if(e1.time < e2.time)
		return true;
	else if(e1.time==e2.time && e1.type<e2.type)
		return true;
	else if(e1.time==e2.time && e1.type==e2.type && e1.key<e2.key)
		return true;
	return false;
}
int main()
{
	cin>>n>>k;
	vector<Event> v;
	Event e;
	int key,start,last;
	for(int i=0;i<k;i++)
	{
		cin>>key>>start>>last;
		e.key=key, e.time=start, e.type=Borrow;
		v.push_back(e);
		e.time=start+last, e.type=Return;
		v.push_back(e);
	}
	sort(v.begin(),v.end(),cmp); 

	for(int i=1;i<=n;i++)
		box[i]=i;
	for(int i=0;i<v.size();i++)
	{
		if(v[i].type == Borrow)
		{
			for(int j=1;j<=n;j++)
			{
				if(box[j]==v[i].key)
				{
					box[j]='X';
					break;
				}
			}
		}
		else
		{
			for(int j=1;j<=n;j++)
			{
				if(box[j]=='X')
				{
					box[j]=v[i].key;
					break;
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
		cout<<box[i]<<' ';
}


