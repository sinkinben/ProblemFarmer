/*
	100�ְ汾

	������SHOP���Ž����У�ͬʱBFS
	��ʾ��Դ��https://blog.csdn.net/qq_20916555/article/details/51103996

	�ӵ㣺
	39�е�continue�Ǵ���ģ���Ϊ����ͻ�1֮�󣬿��ܴ��ڣ��ͻ�2�ڿͻ�1�Ա�
*/
#include<iostream>
#include<queue>
#define SHOP 1
#define MINE 2
#define CLIENT 3
#define MAXN 1001
#define OutOfBound(x) ((x<=0)||(x>n))
using namespace std;
struct State {
	int x, y;
	int step;
	State(int xx = -1, int yy = -1, int ss = 0) :x(xx), y(yy), step(ss) {}
};
int n, m, k, d;
int a[MAXN][MAXN] = { {0} };
bool vis[MAXN][MAXN] = { {false} };
queue<State> q;

void bfs()
{
	unsigned long long ans = 0;
	State now;
	int x, y, step;
	while (!q.empty())
	{
		now = q.front();
		x = now.x, y = now.y, step = now.step;
		q.pop();
		if (a[x][y] > CLIENT)	//�õ��ǿͻ�
		{
			ans += (a[x][y] - CLIENT)*step;
			//continue;
		}
		if (!OutOfBound(y - 1) && !vis[x][y - 1] && a[x][y - 1] != MINE)
		{
			vis[x][y - 1] = 1;
			q.push(State(x, y - 1, step + 1));
		}
		if (!OutOfBound(x - 1) && !vis[x - 1][y] && a[x - 1][y] != MINE)
		{
			vis[x - 1][y] = 1;
			q.push(State(x - 1, y, step + 1));
		}
		if (!OutOfBound(y + 1) && !vis[x][y + 1] && a[x][y + 1] != MINE)
		{
			vis[x][y + 1] = 1;
			q.push(State(x, y + 1, step + 1));
		}
		if (!OutOfBound(x + 1) && !vis[x + 1][y] && a[x + 1][y] != MINE)
		{
			vis[x + 1][y] = 1;
			q.push(State(x + 1, y, step + 1));
		}
	}
	cout << ans << endl;
}
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> m >> k >> d;
	int x, y, z;
	for (int i = 0; i < m; i++)
	{
		cin >> x >> y;
		a[x][y] = SHOP;
		q.push(State(x, y, 0));
		vis[x][y] = true;
	}
	//a[x][y]>CLIENT,��ʾ�õ���client��a[x][y]-CLIENT��ʾ����
	for (int i = 0; i < k; i++)
	{
		cin >> x >> y >> z;
		if (a[x][y] == 0)
			a[x][y] = CLIENT + z;
		else
			a[x][y] += z;
	}
	for (int i = 0; i < d; i++)
	{
		cin >> x >> y;
		a[x][y] = MINE;
	}
	bfs();

}