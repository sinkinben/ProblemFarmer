/*
	30分版本
	正则表达式，只处理2级json的情况
*/
#include<iostream>
#include<sstream>
#include<regex>
#include<string>
#include<map>
#define _STR 0
#define _OBJ 1
#define _NOT 2
using namespace std;
const char * output[] = { "STRING","OBJECT","NOTEXIST" };
int n, m;
map<string, string> jsonMap;
void replaceAll(string &source, string pattern, string target)
{
	int pos = source.find(pattern);
	while (pos != -1)
	{
		source.replace(pos, pattern.length(), target);
		pos = source.find(pattern);
	}
}
vector<string> split(string &str)
{
	istringstream ss(str);
	string s;
	vector<string> res;
	while (ss >> s)
		res.push_back(s);
	return res;
}
int main()
{

	//cout << regex_match(s, regex("(\"[!-~]+\":\\s*\"[!-~]+\")"));
	ios::sync_with_stdio(0);
	cin >> n >> m;
	cin.ignore();
	string jsonStr = "";
	for (int i = 0; i < n; i++)
	{
		string s;
		getline(cin, s);
		jsonStr += s;
	}
	jsonStr.insert(jsonStr.end() - 1, ',');	//为正则匹配做准备
	//cout << jsonStr << endl;
	//方便匹配和输出
	replaceAll(jsonStr, "\\\\", "\\");
	replaceAll(jsonStr, "\\\"", "\"");

	regex r1("(\"[!-~]+\":\\s*\"[!-~]+\",)");	//匹配<string>:<string>类型的pair
	smatch smth;
	while (regex_search(jsonStr, smth, r1))
	{
		string line = smth.str(0);
		line.pop_back();
		replaceAll(line, ": ", " ");
		vector<string> vs = split(line);
		jsonMap[vs[0]] = vs[1];
		jsonStr = smth.suffix().str();
	}

	while (m--)
	{
		string s;
		cin >> s;
		cin.ignore();
		s = "\"" + s + "\"";
		if (jsonMap.find(s) == jsonMap.end())
			cout << output[_NOT] << endl;
		else
		{
			cout << output[_STR] << ' ';
			string val = jsonMap[s];
			val = val.substr(1);
			val.pop_back();
			cout << val << endl;
		}
	}
}

/*
	5 5
	{
	"firstName": "John",
	"lastName": "Smith",
	"esc\\aped": "\"hello\""
	}
	firstName
	address
	address.city
	address.postal
	esc\aped
*/