#include<bits/stdc++.h>
using namespace std;
bool sensitive=false;
string target;
int N=0;

string toUpper(string s)
{
	int len=s.length();
	for(int i=0;i<len;i++)
	{
		if('a'<=s[i] && s[i]<='z')
			s[i]=s[i]-'a'+'A';
	}
	return s;
}

int main()
{
	cin>>target;
	cin.ignore();
	cin>>sensitive;
	cin.ignore();
	cin>>N;
	
	if(!sensitive)
		target=toUpper(target);
	string s;
	for(int i=0;i<N;i++)
	{
		cin>>s;
		string tmp(s);
		if(!sensitive)
			s=toUpper(s);
		if(s.find(target)!=string::npos)
		{
			cout<<tmp<<endl;
			continue;
		}
	}
	
}
