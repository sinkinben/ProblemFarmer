#include<regex>
#include<string>
#include<iostream>
#include<vector>
#define _INT 0
#define _STR 1
#define _PATH 2
using namespace std;
const char* ruleType[] = { "<int>","<str>","<path>" };
const char* regexStr[] = { "([0-9]+)","([A-Za-z_]+)","([a-zA-Z0-9/_\\.]+)" };

struct UrlRule {
	string rule;
	string name;
	vector<int> vtype;
	UrlRule(string rr = "", string nn = "", int tt=-1) 
	:rule(rr), name(nn){}
};

int n, m;
vector<UrlRule> vrules;
vector<string> vurls;
void replaceAll(string &src, string pattern, string target)
{
	int pos = src.find(pattern);
	while (pos != -1)
	{
		src.replace(pos, pattern.length(), target);
		pos = src.find(pattern);
	}
}
void init()
{
	cin >> n >> m;
	cin.ignore();
	for (int i = 0; i < n; i++)
	{
		string p, r;
		cin >> p;
		cin.ignore();
		cin >> r;
		cin.ignore();
		vrules.push_back(UrlRule(p, r));
	}
	int size = vrules.size();
	for (int i = 0; i < size; i++)
	{
		if (vrules[i].rule.find(ruleType[_INT]) != -1)
			replaceAll(vrules[i].rule, ruleType[_INT], regexStr[_INT]);
		if (vrules[i].rule.find(ruleType[_STR]) != -1)
			replaceAll(vrules[i].rule, ruleType[_STR], regexStr[_STR]);
		if (vrules[i].rule.find(ruleType[_PATH]) != -1)
			replaceAll(vrules[i].rule, ruleType[_PATH], regexStr[_PATH]);
	}
}

void urlMatch(string &q)
{
	for (UrlRule x : vrules)
	{
		smatch sm;
		if (regex_match(q, sm, regex(x.rule)))
		{
			cout << x.name << ' ';
			for (int i = 1; i < sm.size(); i++)
			{
				if (regex_match(sm.str(i), regex("([0]+)([0-9]+)")))
				{
					string s = sm.str(i);
					int len = s.length();
					int k = 0;
					while (s[k++] == '0');
					cout << s.substr(--k) << ' ';
				}
				else
				{
					cout << sm[i] << ' ';
				}
			}
			cout << endl;
			return;
		}
	}
	cout << "404" << endl;
}

int main() {
	ios::sync_with_stdio(0);
	init();
	while (m--)
	{
		string q;
		cin >> q;
		cin.ignore();
		urlMatch(q);
	}
}

/*
URL的规则：
	以/为分隔符
	/开头
	合法：字母、数字、减号、下划线、小数点
*/
