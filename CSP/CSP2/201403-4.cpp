/*
	100分版本
	参考：https://blog.csdn.net/more_ugly_less_bug/article/details/61614761
	利用State+BFS记录搜索的状态
	注意坐标要使用long long，因为平方之后会超出int
*/
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<cmath>
#define MAXN 101
#define MAXKM 101
#define square(x) ((x)*(x))
using namespace std;
struct Node {
	long long x = -1, y = -1;
};
struct State {
	int node = -1;
	int addNum = 0;
	int totalNum = 0;
	State(int nn = -1, int aa = 0, int tt = 0) :node(nn), addNum(aa), totalNum(tt) {}
};

int n, m, k, r;
bool vis[MAXN + MAXKM];
Node node[MAXN + MAXKM];
bool isLinked(int n1, int n2)
{
	return n1!=n2 && sqrt(square(node[n1].x - node[n2].x) + (square(node[n1].y - node[n2].y))) <= r;
}
int bfs(const int start, const int end)
{
	queue<State> q;
	vis[start] = 1;
	State now;
	q.push(State(start, 0, 1));
	while (!q.empty())
	{
		now = q.front();
		q.pop();
		if (now.node == end)
		{
			return now.totalNum - 2;
		}
		for (int i = 0; i < n + m; i++)
		{
			if (isLinked(now.node, i))	//扫描每一个与now连接的点
			{
				if (!vis[i])			//如果没访问过
				{
					if (i >= n && now.addNum == k)	//如果是新设但是不能加入
						continue;
					vis[i] = 1;
					q.push(State(i, now.addNum + (n <= i), now.totalNum + 1));
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	scanf("%d %d %d %d", &n, &m, &k, &r);
	for (int i = 0; i < n + m; i++)
		scanf("%lld %lld", &node[i].x, &node[i].y);
	cout << bfs(0, 1) << endl;
	
}