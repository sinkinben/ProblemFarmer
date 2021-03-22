#include<bits/stdc++.h>
using namespace std;
enum{OBJ=0,STR=1};
int NR=0;
int n,m;
string all="";
vector<string> vs;

int point(string &s)
{
	for(int i=0;i<s.length();i++)
		if(s[i] == '.')
			return i;
	return -1;	
}

int nextColon(int start,string &all)
{
	int len=all.length();
	bool left=true;
	
	for(int i=start+1;i<len;i++)
	{
		if(all[i] == '\"' && all[i-1]!='\\')
			return i;
	}
	return len;
}

int rightBrace(int start,string &all)
{
	assert(all[start] == '{');
	int len=all.length();
	for(int i=start+1;i<len;i++)
	{
		if(all[i] == '}')
			return i;
	}
	return len;
}
void searchSTR(string &s,bool &flag)
{
	int vslen=vs.size();
	for(int i=0;i<vslen;i++)
	{
		if(vs[i] == s && vs[i+1][0]!='{')
		{
			flag=true;
			cout<<"STRING "<<vs[i+1]<<endl;
			return;
		}
		else if(vs[i] == s && vs[i+1][0] == '{')
		{
			flag=true;
			cout<<"OBJECT"<<endl;
			return;
		}
	}
}

void searchOBJ(string &s,int pointpos,bool &flag)
{
	string s1=s.substr(0,pointpos);
	string s2=s.substr(pointpos+1);
	//cout<<s1<<' '<<s2<<endl;
	int index=-1;
	for(int i=0;i<vs.size();i++)
	{
		if(vs[i]==s1)
		{
			index=i+1;
			break;
		}
	}
	if(index==-1 || vs[index].find(s2)==string::npos)
	{
		flag=false;
		return;
	}
	flag=true;
	int colon1=vs[index].find(s2);
	int colon2=nextColon(colon1,vs[index]);
	colon1=nextColon(colon2,vs[index]);
	colon2=nextColon(colon1,vs[index]);
	cout<<"STRING "<<vs[index].substr(colon1+1,colon2-1-colon1)<<endl;
	
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	cin.ignore();
	string s;
	while(n)
	{
		n--;
		getline(cin,s);
		all+=s;
	}
	//cout<<all;
	int j;
	for(int i=1;i<all.length();i++)
	{
		if(all[i] == '\"')
		{
			j=nextColon(i,all);
			vs.push_back(all.substr(i+1,j-1-i));
			i=j+1; 
		}
		else if(all[i] == '{')
		{
			j=rightBrace(i,all);
			vs.push_back(all.substr(i,j-i+1));
			i=j+1;
		}
	}
	
//	for(string &s:vs)
//	{
//		for(int i=0;i<s.length();i++)
//		{
//			if(i+1<s.length() && s[i]=='\\'&& (s[i+1]=='\\' || s[i+1]=='\"'))
//				s.erase(i,1);
//		}
//		//cout<<s<<endl;
//	}
	for(int i=0;i<vs.size();i++)
	{
		for(int j=0;j<vs[i].length();j++)
		{
			if(j+1<vs[i].length() && vs[i][j] == '\\' && (vs[i][j+1]=='\\'||vs[i][j+1]=='\"'))
				vs[i].erase(j,1);
		}
	}
	
	//cin.ignore();
	for(int i=0;i<m;i++)
	{
		bool flag=false;
		getline(cin,s);
		int pointpos=point(s);
		if(pointpos==-1)
			searchSTR(s,flag);
		else
			searchOBJ(s,pointpos,flag);
		if(!flag)
			cout<<"NOTEXIST"<<endl;
	}
}
