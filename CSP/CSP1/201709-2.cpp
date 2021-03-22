#include<bits/stdc++.h>
using namespace std;
struct Event{
	int time;
	int key;
	bool borrow;
	Event(int t=-1, int k=-1,bool b=false)
	:time(t), key(k), borrow(b){} 
};
vector<Event> v;
int N,K;
bool cmp(Event e1, Event e2)
{
	if(e1.time < e2.time)
		return true;
	else if(e1.time == e2.time && !e1.borrow && e2.borrow)
		return true;
	else if(e1.time == e2.time && e1.borrow==e2.borrow && e1.key<e2.key)
		return true;
	return false;
}

int getKeyIndex(char key[],int keyOrder)
{
	for(int i=1;i<=N;i++)
		if((int)(key[i]-'0') == keyOrder)
			return i;
	assert(0);
	return -1;
}

int main()
{
	cin>>N>>K;
	char key[N+3];
	for(int i=1;i<=N;i++)
		key[i]=i+'0';
	int w,s,c;
	for(int i=0;i<K;i++)
	{
		cin>>w>>s>>c;
		Event e1(s,w,true), e2(s+c,w,false);
		v.push_back(e1);
		v.push_back(e2);
	}
	sort(v.begin(),v.end(),cmp);
//	for(Event &e:v)
//		cout<<e.time<<' '<<e.borrow<<' '<<e.key<<endl;
	for(int i=0;i<v.size();i++)
	{
		if(v[i].borrow)
		{
			int index=getKeyIndex(key,v[i].key);
			key[index]='X';
		}
		else
		{
			for(int j=1;j<=N;j++)
			{
				if(key[j]=='X')
				{
					key[j]=v[i].key+'0';
					break;
				}
			}
		}
	}
	for(int i=1;i<=N;i++)
		cout<<key[i]<<' ';
	cout<<endl;
	return 0;
} 
