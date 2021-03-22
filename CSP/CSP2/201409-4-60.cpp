/*
	60分版本，运行超时（ans换成unsigned long long +10分）
	对每一个顾客vclient[i]实行BFS，求出最优

	对vclient排序去重后还是60 
	=____________=
*/
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string.h>
#include<cassert>
#define MAXN 1001
#define SHOP 1
#define CLIENT 2
#define MINE 3
#define OutOfBound(x,y) ((x<=0)||(x>n)||(y<=0)||(y>n))
using namespace std;
struct State {
	int x, y;
	int step;
	State(int xx = -1, int yy = -1, int ss = -1) :x(xx), y(yy), step(ss) {}
};
struct Client {
	int x = -1, y = -1, n = 0;
	Client(int xx = -1, int yy = -1, int nn = 0) :x(xx), y(yy), n(nn) {}
	bool operator < (const Client &c) const {
		if (x < c.x)
			return true;
		else if (x == c.x && y < c.y)
			return true;
		return false;
	}
};
int n, m, k, d;
int a[MAXN][MAXN] = { {0} };
bool vis[MAXN][MAXN] = { {0} };
vector<Client> vclient;

int bfs(Client &c)
{
	queue<State> q;
	memset(vis, 0, sizeof(vis));
	State now;
	int x, y;
	q.push(State(c.x, c.y, 0));
	vis[c.x][c.y] = 1;
	while (!q.empty())
	{
		now = q.front();
		q.pop();
		x = now.x;
		y = now.y;
		if (a[x][y] == SHOP)
		{
			//cout << now.x << ' ' << now.y << ' ' << now.step << endl;
			return now.step;
		}
		if (!OutOfBound(x, y - 1) && !vis[x][y - 1] && a[x][y - 1] != MINE)
		{
			vis[x][y - 1] = 1;
			q.push(State(x, y - 1, now.step + 1));
		}
		if (!OutOfBound(x - 1, y) && !vis[x - 1][y] && a[x - 1][y] != MINE)
		{
			vis[x - 1][y] = 1;
			q.push(State(x - 1, y, now.step + 1));
		}
		if (!OutOfBound(x, y + 1) && !vis[x][y + 1] && a[x][y + 1] != MINE)
		{
			vis[x][y + 1] = 1;
			q.push(State(x, y + 1, now.step + 1));
		}
		if (!OutOfBound(x + 1, y) && !vis[x + 1][y] && a[x + 1][y] != MINE)
		{
			vis[x + 1][y] = 1;
			q.push(State(x + 1, y, now.step + 1));
		}
	}
	exit(-1);
	return 0;
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
	}
	for (int i = 0; i < k; i++)
	{
		cin >> x >> y >> z;
		vclient.push_back(Client(x, y, z));
	}
	sort(vclient.begin(), vclient.end());
	//去重以减少BFS的次数
	for (int i = 0; i < vclient.size(); i++)
	{
		int j = i;
		int num = 0;
		while (j < vclient.size() && vclient[j].x == vclient[i].x && vclient[j].y == vclient[i].y)
			num+=vclient[j].n, j++;
		//[i,j-1]是同一个地点
		vclient[i].n = num;
		if (i + 1 < vclient.size())
			vclient.erase(vclient.begin() + i + 1, vclient.begin() + j);
	}


	for (int i = 0; i < d; i++)
	{
		cin >> x >> y;
		a[x][y] = MINE;
	}

	unsigned long long ans = 0;
	int vsize = vclient.size();
	for (int i = 0; i < vsize; i++)
	{
		ans += bfs(vclient[i])*vclient[i].n;
	}
	cout << ans << endl;

}