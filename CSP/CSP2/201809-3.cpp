#include<iostream>
#include<vector>
#include<algorithm>
#include<sstream>
#include<bits/stdc++.h>
#define MAX_LEN 101
static int len = 0;
using namespace std;
struct Line{
	string label="";
	string id="";
	int level=-1;
};
int n,m;
Line line[MAX_LEN];
int getLevel(string &s)
{
	int slen = s.length();
	int points = 0;
	for(int i=0;i<slen;i++)
	{
		if(s[i]=='.')
			points++;
		else
			break;
	}
	return points/2;
}
vector<string> split(string &str)
{
	istringstream ss(str);
	string s;
	vector<string> res;
	while(ss>>s)
		res.push_back(s);
	return res;
}
void replace(string &src, string pattern, string target)
{
	int pos = src.find(pattern);
	while(pos!=-1)
	{
		src.replace(pos,pattern.length(),target);
		pos = src.find(pattern);
	}
}
void print(vector<int> &v)
{
	cout<<v.size()<<' ';
	for(int x:v)
		cout<<x<<' ';
	cout<<endl;
}
void idSelector(string &selector)
{
	vector<int> v;
	for(int i=0;i<len;i++)
	{
		if(line[i].id == selector)
			v.push_back(i+1);
	}
	print(v);
} 
void labelSelector(string &selector)
{
	vector<int> v;
	for(int i=0;i<len;i++)
	{
		if(line[i].label == selector)
			v.push_back(i+1);
	}
	print(v);
} 
//void childSelector(string &selector)		//60分版本的后代选择器，只处理了2级的情况 
//{
//	vector<int> ans;
//	vector<string> vs = split(selector);
//	for(int i=0;i<len;i++)
//	{
//		if(line[i].label == vs[0])
//		{
//			for(int j=i+1;j<len;j++)
//			{
//				if(line[j].level == line[i].level+1 &&
//				   line[j].label == vs[1])
//				   {
//						ans.push_back(j+1);
//				   }
//				else if(line[j].level!=line[i].level+1)
//					break;
//			}
//		}
//	}
//	print(ans); 
//} 
int getPreNodeIndex(int index)
{
	int level = line[index].level;
	for(int i=index-1;i>=0;i--)
	{
		if(line[i].level == level-1)
		{
			//cout<<"pre="<<i<<endl;
			return i;
		}
	}
	return -1;
}

void childSelector(string &selector)//50分版本，处理多级后代选择器 
{
	vector<int> ans;
	vector<string> sec = split(selector);
	reverse(sec.begin(),sec.end());
	int size = sec.size();
	for(int i=len-1;i>=0;i--)
	{
		if(line[i].label==sec[0] || line[i].id==sec[0])
		{
			int match=1;
			int pre=getPreNodeIndex(i);
			while(line[pre].label==sec[match] || line[pre].id==sec[match])
			{
				match++;
				pre=getPreNodeIndex(pre);
				if(pre==-1 || match==size)
					break;
			}
			if(match==size)
				ans.push_back(i+1);
		}
	}
	sort(ans.begin(),ans.end());
	print(ans);
	
} 
int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>m;
	cin.ignore();
	
	cin>>line[len].label;
	cin.ignore();
	line[len].level=0;
	len++;
	string s;
	for(int i=0;i<n-1;i++)
	{
		getline(cin,s);
		int level = getLevel(s);
		replace(s,"..","");
		vector<string> vs = split(s);
		transform(vs[0].begin(),vs[0].end(),vs[0].begin(),::tolower);
		int size = vs.size();
		
		if(size == 1)
			line[len].label=vs[0];
		else if(size == 2)
		{
			line[len].label=vs[0];
			line[len].id=vs[1];
		}
		line[len++].level = level;
		s.clear();
	}
	while(m--)
	{
		string selector;
		getline(cin,selector);
		if(selector[0] == '#')
			idSelector(selector);
		else if(selector.find(" ")==-1)
			labelSelector(selector);
		else
			childSelector(selector);
	}
	
}


/*
	11 5
	html
	..head
	....title
	..body
	....h1
	....p #subtitle
	....div #main
	......h2
	......p #one
	......div
	........p #two
	p
	#subtitle
	h3
	div p
	div div p
*/


