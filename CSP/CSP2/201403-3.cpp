/*
	90�ְ汾
	�ӵ㣺
	abcw:
	1. ls -a -b -		(���ֵ�����-)
	2. ls -a doc doc	(a��һ�γ��֣����漴ʹ���ֲ���Ҳ�ǺϷ�)
	3. ls -ab			(����-ab������������Ҫ��opt������2)
*/
#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<map>
#include<assert.h>
#define HASH_INDEX(c) (c-'a')
using namespace std;
bool option[26] = { 0 };
bool args[26] = { 0 };
int casei = 1;
const char * caseStr = "Case ";
vector<string> split(string &str)
{
	istringstream ss(str);
	string s;
	vector<string> res;
	while (ss >> s)
		res.push_back(s);
	return res;
}
void print(map<string, string> &m)
{
	cout << caseStr << casei++ << ": ";
	
	for (pair<string, string> p : m)
	{
		cout << p.first << ' ';
		if (p.second != "")
			cout << p.second << ' ';
	}

	cout << endl;
}

int main()
{
	ios::sync_with_stdio(0);
	string s;
	cin >> s;
	cin.ignore();
	int len = s.length();
	for (int i = 0; i < len; i++)
	{
		if (s[i] == ':')
			args[HASH_INDEX(s[i - 1])] = true;
		else
			option[HASH_INDEX(s[i])] = true;
	}
	int n;
	cin >> n;
	cin.ignore();
	while (n--)
	{
		s.clear();
		getline(cin, s);
		vector<string> vs = split(s);
		map<string, string> m;
		int size = vs.size();
		int i = 1;
		if (size==1 || (i < size && vs[i][0] != '-'))
		{
			print(m);
			continue;
		}
		for (i = 1; i < size; i++)
		{
			string &opt = vs[i];
			if (opt.length() == 2 && opt[0] == '-' && option[HASH_INDEX(opt[1])])
			{
				if (args[HASH_INDEX(opt[1])])
				{
					//opt�в�����Ҫ��vs[i+1]�����ǲ����Һ������������
					if (i + 1 == size || (vs[i + 1][0] == '-'))//���������ݻ�vs[i+1]�ǲ���
						break;
					else
						m[opt] = vs[++i];
				}
				else
				{
					//opt�޲�����Ҫ��vs[i+1]�ǲ��������������
					if (i+1<size && vs[i + 1][0] != '-')	//vs[i+1]�ǲ���
					{
						if (m.find(opt) == m.end())//�����һ�γ���
							m[opt] = "";
						else
							break;
					}
					else
						m[opt] = "";
				}
			}
			else
			{
				break;
			}
		}
		print(m);
	}

}
