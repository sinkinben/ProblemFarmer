#include<iostream>
using namespace std;
int a[1001][1001] = { {0} };
int n, m;
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			cin >> a[i][j];
	for (j = m - 1; j >= 0; j--)
	{
		for (i = 0; i < n; i++)
			cout << a[i][j] << ' ';
		cout << endl;
	}
}