/*
	送分题 = = 
	100分版本
*/
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
string target;
int sensitive;
int n;
int main()
{
	ios::sync_with_stdio(0);
	cin >> target;
	cin.ignore();
	cin >> sensitive;
	cin.ignore();
	cin >> n;
	cin.ignore();

	if (sensitive == 0)
		transform(target.begin(), target.end(), target.begin(), ::tolower);
	string str;
	while (n--)
	{
		str.clear();
		cin>>str;
		cin.ignore();
		string buf(str);
		if(sensitive == 0)
			transform(str.begin(), str.end(), str.begin(), ::tolower);
		if (str.find(target) != -1)
			cout << buf << endl;
	}
}
