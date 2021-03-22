#include<iostream>
#include<sstream>
#include<vector>
#include<string>
#include<map>
/*
	90分版本，递归处理了多级json
*/
using namespace std;
vector<string> split(string &str);
void replaceAll(string &source, string pattern, string target);
map<string, string> buildJsonMap(string jsonStr);
void simpleJson(string &str, map<string, string> &jsonMap);
void complexJson(string &str, map<string, string> &jsonMap);

int main()
{
	int n, m;
	string jsonStr = "";
	ios::sync_with_stdio(0);
	cin >> n >> m;
	cin.ignore();

	while (n--)
	{
		string s;
		getline(cin,s);
		jsonStr += s;
	}
	//预处理
	replaceAll(jsonStr, "\\\\", "\\");
	replaceAll(jsonStr, "\\\"", "\"");
	//去空格
	replaceAll(jsonStr, " ", "");

	//cout << jsonStr << endl;
	map<string, string> jsonMap=buildJsonMap(jsonStr);

	while (m--)
	{
		string str;
		cin >> str;
		cin.ignore();
		if (str.find(".") == -1)
			simpleJson(str, jsonMap);
		else
			complexJson(str, jsonMap);
	}
	
	


}
/*

5 5
{
"firstName": "John",
"lastName": "Smith",
"esc\\aped": "\"hello\""
}

10 5
{
"firstName": "John",
"lastName": "Smith",
"address": {
"streetAddress": "2ndStreet",
"city": "NewYork",
"state": "NY"
},
"esc\\aped": "\"hello\""
}
firstName
address
address.city
address.postal
esc\aped
*/
void simpleJson(string &str, map<string, string> &jsonMap)
{
	if (jsonMap.find(str) == jsonMap.end())	//一级，不存在
		cout << "NOTEXIST" << endl;
	else//存在
	{
		string val = jsonMap[str];
		if (val[0] == '{')
			cout << "OBJECT" << endl;
		else if (val[0] == '\"')
			cout << "STRING " << val.substr(1, val.length() - 2) << endl;
	}
}

void complexJson(string &str, map<string, string> &jsonMap)
{
	int i = 0;
	while (str[i] != '.')
		i++;
	string s1 = str.substr(0, i);
	string s2 = str.substr(i + 1);
	//cout << s1 << " " << s2 << endl;
	//cout << jsonMap[s1] << endl;
	if (jsonMap.find(s1) == jsonMap.end())
	{
		cout << "NOTEXIST" << endl;
		return;
	}
	else
	{
		string val = jsonMap[s1];
		if (val[0] == '{')
		{
			map<string, string> mm = buildJsonMap(val);
			if (s2.find(".") == -1)
				simpleJson(s2, mm);
			else
				complexJson(s2, mm);
		}
		else
		{
			cout << "NOTEXIST" << endl;
		}
	}

}


map<string,string> buildJsonMap(string jsonStr)
{
	//去除头尾的{}
	jsonStr = jsonStr.substr(1, jsonStr.length() - 2);
	map<string, string> mm;
	while (jsonStr.length() != 0)
	{
		int i = 0;
		while (i<jsonStr.length() && jsonStr[i] != ',')
		{
			if (jsonStr[i] == '{')
			{
				//jump out of {...} object block
				int flag = 1;
				while (flag != 0)
				{
					i++;
					if (jsonStr[i] == '{')
						flag++;
					else if (jsonStr[i] == '}')
						flag--;
				}
			}
			i++;
		}
		string tmp = jsonStr.substr(0, i);
		int index = 0;
		while (tmp[index] != ':')
			index++;
		string key = tmp.substr(1, index-2);
		string val = tmp.substr(index + 1);
		//cout << key << " " << val << endl;
		mm[key] = val;
		if (i == jsonStr.length())
			break;
		jsonStr = jsonStr.substr(i+1);
	}
	return mm;
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
void replaceAll(string &source, string pattern, string target)
{
	int pos = source.find(pattern);
	while (pos != -1)
	{
		source.replace(pos, pattern.length(), target);
		pos = source.find(pattern);
	}
}

