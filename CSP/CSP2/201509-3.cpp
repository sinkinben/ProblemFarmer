/*
	90分版本
	正则表达式真香
	regex库真牛逼
*/
#include<iostream>
#include<string>
#include<regex>
#define MAXMN 101
using namespace std;
int m, n;
string templates[MAXMN];
string varLeft = "{{ ";
string varRight = " }}";
const char* regexStr = "\\{\\{ [a-zA-Z0-9_]+ \\}\\}";
int tlen = 0;
void replaceAll(string &source, string pattern, string target)
{
	int pos = source.find(pattern);
	while (pos != -1)
	{
		source.replace(pos, pattern.length(), target);
		pos = source.find(pattern);
	}
}
void splitKeyVal(string &line, string &key, string &val)
{
	int space = line.find(' ');
	key = line.substr(0, space);
	val = line.substr(space + 2);
	val.pop_back();	//去最后的"
}
void helper(string &key, string &val)
{
	for (int i = 0; i < tlen; i++)
	{
		replaceAll(templates[i], key, val);
	}
}
void clearTemplates()
{
	smatch smth;
	regex rgx(regexStr);
	for (int i = 0; i < tlen; i++)
	{
		string s = templates[i];
		while (regex_search(s, smth, rgx))
		{
			//cout << smth[0] << endl;
			replaceAll(templates[i], smth.str(0), "");
			s = smth.suffix().str();
		}
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin >> m;
	cin >> n;
	cin.ignore();
	while (m--)
		getline(cin, templates[tlen++]);
	string key, val;
	string line;
	while (n--)
	{
		key.clear();
		val.clear();
		line.clear();
		getline(cin, line);
		splitKeyVal(line, key, val);
		helper(key, val);
	}
	clearTemplates();
	for (int i = 0; i < tlen; i++)
	{
		cout << templates[i] << endl;
	}
}

/*
11 2
<!DOCTYPE html>
<html>
<head>
<title>User {{ name }}</title>
</head>
<body>
<h1>{{ name }}</h1><h1>{{ name }}</h1>
<p>Email: <a href="mailto:{{ email }}">{{ email }}</a></p>
<p>Address: {{ address }}</p>
</body>
</html>
name "David Beckham"
email "david@beckham.com"

*/