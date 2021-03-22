/*
	20�� = = 
	ͨ��m==2����������
	ԭ�����뷨����2*6����һ��cell����n*m�ľ��󻮷�Ϊ���ɸ�cell��ÿ��cell����״̬����pow(2,n*m/6)
	��������{n,m}={6,4}��������18
	����һ�ַ�cellƴ�����£�
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
	//��ƭ20��
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