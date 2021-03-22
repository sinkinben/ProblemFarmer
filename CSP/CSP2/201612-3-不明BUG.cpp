#include<iostream>
#include<bits/stdc++.h>
#include<set> 
#include<vector>
#define Cate Category
#define MAXP 101
#define MAXR 101
#define MAXU 101
using namespace std;

struct Category{
	string name;
	int level=-1;
	bool operator <(const Category &c) const
	{
		if(name != c.name)
			return true;
		else if(level >= c.level)
			return true;
		return false;//œ‡µ»‘Úfalse 
	}
};
struct Role{
	string name;
	vector<Category> v;
};
struct User{
	string name;
	set<Category> cateSet;
};
int p,r,u;
Category cate[MAXP];
Role role[MAXR];
User user[MAXU];
int catelen=0;
int rolelen=0;
int userlen=0;
Category categoryHandler(string &s);
vector<string> split(string &str);
int searchRole(string &roleName, int start);
void searchUser(string &name, string &privilege);
int main()
{	

//	Category c1,c2;
//	c1.name = c2.name = "cccc";
//	c1.level = 3;
//	c2.level = 4;
//	set<Category> sss;
//	sss.insert(c1);
//	sss.insert(c2);
//	for(Category ccc:sss)
//		cout<<ccc.name<<' '<<ccc.level<<endl;
		
	ios::sync_with_stdio(0);
	cin>>p;
	cin.ignore();
	string s;
	while(p--)
	{
		s.clear();
		cin>>s;
		cin.ignore();
		cate[catelen++]=categoryHandler(s);
	}
	cin>>r;
	cin.ignore();
	while(r--)
	{
		s.clear();
		getline(cin,s);
		vector<string> vs = split(s);
		role[rolelen].name = vs[0];
		int size = vs.size();
		for(int i=2;i<size;i++)
			role[rolelen].v.push_back(categoryHandler(vs[i]));
		for(Cate cate:role[rolelen].v)
			cout<<cate.name<<" "<<cate.level<<endl;
		cout<<endl;
		rolelen++;	
	}
	cin>>u;
	cin.ignore();
	while(u--)
	{
		s.clear();
		getline(cin,s);
		vector<string> vs = split(s);
		user[userlen].name = vs[0];
		int size = vs.size();
		for(int i=2;i<size;i++)
		{
			int k = searchRole(vs[i],0);
			while(k<rolelen)
			{
				user[userlen].cateSet.insert(role[k].v.begin(),role[k].v.end());
				k = searchRole(vs[i],k+1);
			}
		}
		userlen++;
	}
	
	for(int i=0;i<userlen;i++){
		cout<<user[i].name<<endl;
		for(Category c:user[i].cateSet)
			cout<<c.name<<" "<<c.level<<endl;
		cout<<endl;
	}
	
	int q;
	cin>>q;
	cin.ignore();
	string usrname, privilege;
	while(q--)
	{
		usrname.clear();
		privilege.clear();
		cin>>usrname;
		cin>>privilege;
		cin.ignore();
		
		searchUser(usrname,privilege);
	}
	
}

void level(const set<Category> &s, const string &privilege)
{
	Category c;
	int k = privilege.find(":");
	c.name = privilege.substr(0,k);
	set<Category>::iterator itor = s.find(c);
	
	
	if(itor == s.end())
		cout<<"false"<<endl;
	else
	{
		Category ccc = *itor;
		int targetlevel = privilege.substr(k+1)[0]-'0';
		if(ccc.level >= targetlevel)
			cout<<"true"<<endl;
		else
			cout<<"false"<<endl;
	}
}

void non_level(const set<Category> &s, const string &privilege)
{
	Category c;
	c.name = privilege;
	set<Category>::iterator itor = s.find(c);

	if(itor == s.end())
		cout<<"false"<<endl;
	else
	{
		Category ccc = *itor;
		if(ccc.level == -1)
			cout<<"true"<<endl;
		else
			cout<<ccc.level<<endl;
	}
}

void searchUser(string &name, string &privilege)
{
	int k=0;
	for(k=0;k<userlen;k++)
	{
		if(user[k].name == name)
			break;
	}
	if(k == userlen)
	{
		cout<<"false"<<endl;
		return;
	}
	set<Category>& s = user[k].cateSet;
	if(privilege.find(":") == -1)
		non_level(s,privilege);
	else
		level(s,privilege);
}

int searchRole(string &roleName, int start)
{
	for(int i=start;i<rolelen;i++)
		if(role[i].name == roleName)
			return i;
	return rolelen;
}


Category categoryHandler(string &s)
{
	Category c;
	int k = s.find(":");
	if(k==-1)
		c.name = s;
	else
	{
		c.name = s.substr(0,k);
		c.level = s.substr(k+1)[0]-'0';
	}
	return c;
}

vector<string> split(string &str)
{
	istringstream ss(str);
	string s;
	vector<string> res;
	while(ss>>s)
	{
		res.push_back(s);
	}
	return res;
}


