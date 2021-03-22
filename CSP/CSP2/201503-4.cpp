/*
	100分版本
	看了网上的提示：是求一棵树的直径
	只要任意找到一个点，然后bfs找到离他最远的那个点，然后再从那个点开始bfs，找到的最大距离就是所求的。
	想想还真是这么一回事，真香
*/
#include<iostream>
#include<algorithm>
#include<string.h>
#include<vector>
#include<map>
#include<queue>
#define VMAX 20005
using namespace std;
struct State {
	int step = 0;
	int node = 0;
	State(int ss = 0, int nn = 0) :step(ss), node(nn) {}
};
int n, m;
bool vis[VMAX] = { 0 };
vector<int> edge[VMAX];
map<int, int> order;
State bfs(int start)
{
	queue<State> q;
	State ret(-1,-1);
	memset(vis, 0, sizeof(vis));
	State now(0, start);
	q.push(now);
	vis[now.node] = 1;
	while (!q.empty())
	{
		now = q.front();
		q.pop();
		if (now.step > ret.step)
		{
			ret = now;
		}
		int node = now.node;
		for (int x : edge[node])
		{
			if (!vis[x])
			{
				vis[x] = 1;
				q.push(State(now.step + 1, x));
			}
		}
	}
	return ret;

}
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	int t;
	//节点[1,n]表示交换机
	for (int i = 2; i <= n; i++)
	{
		cin >> t;
		edge[i].push_back(t);
		edge[t].push_back(i);
	}
	//节点[n+1,n+m]表示终端电脑
	for (int i = n + 1; i <= n + m; i++)
	{
		cin >> t;
		edge[i].push_back(t);
		edge[t].push_back(i);
	}
	
	State s1 = bfs(1);
	State s2 = bfs(s1.node);
	cout << s2.step << endl;
}