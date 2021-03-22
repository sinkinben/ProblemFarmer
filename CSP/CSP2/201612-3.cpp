/*
	0分的版本
	妈蛋，不知到错哪里
	2019/03/06 20:35

	100分版本
	原因是中间输出忘记删除了
	2019/03/09
	=___________=
*/
#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<algorithm>
#define MAXPRU 101
#define MAXQ 10001
using namespace std;
struct Category{
	string name;
	int level = -1;
	Category& operator =(const Category &c) {
		name = c.name;
		level = c.level;
		return *this;
	}

	bool operator < (const Category &c) const {
		if (name < c.name)
			return true;
		else if (name == c.name && level > c.level)
			return true;
		return false;
	}
};
struct Role {
	string name;
	vector<Category> v;
};
typedef Role User;


int p, r, u, q;
Category category[MAXPRU];
Role role[MAXPRU];
User user[MAXPRU];
int catelen = 0;
int rolelen = 0;
int userlen = 0;

Category getCategory(string &s);
vector<string> splitString(string str);
int searchRole(string &roleName, int start);
void searchUser(string &userName, string &pri);
void unique(vector<Category> &v);
int main()
{
	ios::sync_with_stdio(0);
	cin >> p;
	cin.ignore();
	string s;
	while (p--)
	{
		s.clear();
		cin >> s;
		cin.ignore();
		category[catelen++] = getCategory(s);
	}
	cin >> r;
	cin.ignore();
	while (r--)
	{
		s.clear();
		getline(cin, s);
		vector<string> vs = splitString(s);
		role[rolelen].name = vs[0];
		int size = vs.size();
		for (int i = 2; i < size; i++)
			role[rolelen].v.push_back(getCategory(vs[i]));
		rolelen++;
	}
	cin >> u;
	cin.ignore();
	while (u--)
	{
		s.clear();
		getline(cin, s);
		vector<string> vs = splitString(s);
		user[userlen].name = vs[0];
		int size = vs.size();
		for (int i = 2; i < size; i++)
		{
			int index = searchRole(vs[i],0);
			while (index < rolelen)
			{
				user[userlen].v.insert(user[userlen].v.end(),
					role[index].v.begin(),
					role[index].v.end());
				index = searchRole(vs[i], index + 1);
			}
		}
		sort(user[userlen].v.begin(), user[userlen].v.end());
		unique(user[userlen].v);
		//for (Category &c : user[userlen].v)
		//	cout << c.name << ' ' << c.level << endl;
		//cout << endl;

		userlen++;

	}

	cin >> q;
	cin.ignore();
	while (q--)
	{
		string name, pri;
		cin >> name >> pri;
		cin.ignore();
		searchUser(name, pri);
	}
	
}
void with_level(vector<Category> &v, const string &pri)
{
	int k = pri.find(":");
	string name = pri.substr(0, k);
	int level = pri.substr(k + 1)[0] - '0';
	for (Category& c : v)
	{
		if (c.name == name)
		{
			if (level <= c.level)
				cout << "true" << endl;
			else
				cout << "false" << endl;
			return;
		}
	}
	cout << "false" << endl;
}

void non_level(vector<Category> &v, const string &pri)
{
	for (Category& c : v)
	{
		if (c.name == pri)
		{
			if (c.level == -1)
				cout << "true" << endl;
			else
				cout << c.level << endl;
			return;
		}
	}
	cout << "false" << endl;
}

void searchUser(string &userName, string &pri)
{
	int k = 0;
	for (k = 0; k < userlen; k++)
	{
		if (user[k].name == userName)
			break;
	}
	if (k == userlen)
	{
		cout << "false" << endl;
		return;
	}
	vector<Category> &v = user[k].v;
	if (pri.find(":") == -1)
		non_level(v,pri);
	else
		with_level(v,pri);

}

void unique(vector<Category> &v)
{
	if (v.size() == 1)
		return;
	for (int i = 0; i < v.size(); i++)
	{
		int j = i;
		while (j<v.size() && v[i].name == v[j].name)
			j++;
		if (j == v.size() && i+1<v.size())
			v.erase(v.begin() + i + 1);
		else if (j != i + 1)
			v.erase(v.begin()+i+1,v.begin()+j);
	}
}

int searchRole(string &roleName, int start)
{
	for (int i = start; i < rolelen; i++)
	{
		if (role[i].name == roleName)
			return i;
	}
	return rolelen;
}

Category getCategory(string &s)
{
	Category c;
	int k = s.find(":");
	if (k == -1)
		c.name = s;
	else
	{
		string key = s.substr(0, k);
		int val = s.substr(k + 1)[0] - '0';
		c.name = key;
		c.level = val;
	}
	return c;
}
#include<sstream>
vector<string> splitString(string str)
{
	istringstream ss(str);
	string s;
	vector<string> res;
	while (ss >> s)
		res.push_back(s);
	return res;
}




