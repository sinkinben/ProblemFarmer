#include<iostream>
#define isLeap(y) 	((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))
using namespace std;
int calcDayOfWeek(int y, int m, int d)
{
	//Sun=0, Mon=1, Tue=2, ...,
	//Sat=6, w的取值如上
	int w;
	if (m == 1 || m == 2)
		m += 12, y--;
	w = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400 + 1) % 7;
	return w;
}
void print(int y, int m, int d)
{
	cout << y << "/";
	if (m < 10)
		cout << "0" << m << "/";
	else
		cout << m << "/";
	if (d < 10)
		cout << "0" << d << endl;
	else
		cout << d << endl;
}
int a, b, c, year1, year2;
int hashTable[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
int main()
{
	ios::sync_with_stdio(0);
	cin >> a >> b >> c >> year1 >> year2;
	c %= 7;//令Sun=0, Sat=1, ...
	for (int i = year1; i <= year2; i++)
	{
		hashTable[2] = isLeap(i) ? 29 : 28;
		int day = 1;
		int dow = calcDayOfWeek(i, a, day);
		while (dow != c)
			dow = (dow + 1) % 7, day++;	//此时day是a月第1个星期c
		day += (b - 1) * 7;				//此时day是a月第b个星期c
		if (day <= hashTable[a])
			print(i, a, day);
		else
			cout << "none" << endl;
	}
}


