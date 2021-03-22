/*
	20分 = = 
	通过m==2的两个样例
	原来的想法：把2*6看作一个cell，把n*m的矩阵划分为若干个cell，每个cell两种状态，即pow(2,n*m/6)
	错误，例如{n,m}={6,4}，种数有18
	其中一种非cell拼法如下：
	. . * * | 0 0
	. , , * | 1 0
	# # , o | 1 1
	# a o o | 2 2
	@ a a & | 2 0
	@ @ & & | 0 0
*/
#include<iostream>
#include<cmath>
#define ull unsigned long long
#define MOD 1000000007
using namespace std;
ull n, m;
ull ans = 0;
ull myPow(ull x, ull y)
{
	ull t=1;
	while (y--)
	{
		t *= x;
		t %= MOD;
	}
	return t;
}
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	//先骗20分
	//if (m == 2)
	//{
	//	if (n < 3 || n%3!=0)
	//		cout << 0 << endl;
	//	else
	//		cout << myPow(2, n / 3) << endl;
	//	return 0;
	//}
	bool legal1 = (n >= 3 && n % 3 == 0 && m >= 2 && m % 2 == 0);
	bool legal2 = (m >= 3 && m % 3 == 0 && n >= 2 && n % 2 == 0);
	if (!legal1 && !legal2)
	{
		cout << 0 << endl;
		return 0;
	}
	if (legal1)
	{
		n /= 3;
		m /= 2;
		cout << myPow(2, n*m) << endl;
		return 0;
	}
	if (legal2)
	{
		m /= 3;
		n /= 2;
		cout << myPow(2, n*m) << endl;
		return 0;
	}

}