#include<bits/stdc++.h>
using namespace std;
//新的思路：可以把url中的参数替换成对应的<str> <int> <path>然后进行判断 
enum{STR=0, INT=1, PATH=2, SPEC=3};
const string para[3]={"<str>","<int>","<path>"};
int n=0,m=0;
struct Ruler{
	string head="";
	vector<string> para;
	vector<int> type;
	string tail="";
	bool isPath=false;
};
struct URL{
	string head="";
	vector<string> para;
	vector<int> type;
};
bool isNums(string &s)
{
	int len=s.length();
	for(int i=0;i<len;i++)
	{
		if(('a'<=s[i]&&s[i]<='z') || ('A'<=s[i]&&s[i]<='Z'))
			return false;
	}
	return true;
}
bool isChars(string &s)
{
	int len=s.length();
	for(int i=0;i<len;i++)
	{
		if(('0'<=s[i]&&s[i]<='9'))
			return false;
	}
	return true;
}
int getNextVirguleOrSpace(int start, string &s)
{
	int len=s.length();
	for(int i=start+1;i<len;i++)
	{
		if(s[i]=='/'||s[i]==' ')
			return i;
	}
	return len-1;
}

void split(Ruler &r, string &s)
{
	int len=s.length();
	int start=0;
	int end=getNextVirguleOrSpace(start,s);
	r.head=s.substr(start+1,end-start-1);
	start=end;
	end=getNextVirguleOrSpace(start,s);
	while(end!=len-1)
	{
		//string p=(s.substr(start+1,end-start-1));
		if(start+1!=end)
			r.para.push_back((s.substr(start+1,end-start-1)));
		start=end;
		end=getNextVirguleOrSpace(start,s);	
	}
	r.tail=s.substr(start+1);
}

void splitURL(URL &url,string &s)
{
	int len=s.length();
	int start=0;
	int end=getNextVirguleOrSpace(start,s);
	url.head=s.substr(start+1,end-start-1);
	start=end;
	end=getNextVirguleOrSpace(start,s);
	while(end!=len-1)
	{
		if(start+1!=end)
			url.para.push_back(s.substr(start+1,end-start-1));
		start=end;
		end=getNextVirguleOrSpace(start,s);
	}
	if(s[len-1] == '/')
		url.para.push_back(s.substr(start+1,len-2-start));
	else
		url.para.push_back(s.substr(start+1));
		
//	cout<<"head="<<url.head<<endl; 
//	for(int i=0;i<url.para.size();i++)
//		cout<<url.para[i]<<' ';
//	cout<<endl;
//	
}

void getRulerType(Ruler r[],int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<r[i].para.size();j++)
		{
			if(r[i].para[j] == para[STR])
				r[i].type.push_back(STR);
			else if(r[i].para[j] == para[INT])
				r[i].type.push_back(INT);
//			else if(r[i].para[j] == para[PATH])
//				r[i].type.push_back(PATH);
			else
				r[i].type.push_back(SPEC);
		}
	}
}

void getUrlType(URL &u)
{
	for(int j=0;j<u.para.size();j++)
	{
		if(isNums(u.para[j]))
			u.type.push_back(INT);
		else if(isChars(u.para[j]))
			u.type.push_back(STR);
		else
			u.type.push_back(SPEC);
	}
}

void printPath(Ruler &r, URL &u)
{
	cout<<r.tail<<' ';
	int i=0;
	for(i=0;i<u.para.size()-1;i++)
		cout<<u.para[i]<<'/';
	cout<<u.para[i]<<endl;
}

void printString(Ruler &r, URL &u)
{
	cout<<r.tail<<' ';
	for(int i=0;i<u.para.size();i++)
		cout<<u.para[i]<<' ';
	cout<<endl;
}

void check(URL &u, Ruler r[], int n)
{
	int i=0;
	bool found=false;
	for(i=0;i<n;i++)
	{
		if(u.head == r[i].head)
		{
			if(r[i].isPath)
				printPath(r[i],u),found=true;
			else if(u.type == r[i].type)
				printString(r[i],u),found=true;
		}
	}
	if(!found)
		cout<<"404"<<endl;
}

int main()
{
	cin>>n>>m;
	cin.ignore();
	Ruler ruler[n];
	string s;
	for(int i=0;i<n;i++)
	{
		getline(cin,s);
		split(ruler[i],s);
		s.clear();
	}
	//path?
	for(int i=0;i<n;i++)
	{
		if(ruler[i].para[0] == para[PATH])
			ruler[i].isPath=true;
	}
	getRulerType(ruler,n);
	
	//cin.ignore();?
	
	for(int i=0;i<m;i++)
	{
		URL url;
		getline(cin,s);
		splitURL(url,s);
		getUrlType(url);
		check(url,ruler,n);
	}
	
	
}
