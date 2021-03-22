/*
	BFS题目:暴力解法，预测会超时
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
int bfs(int start)
{
	queue<State> q;
	int step = INT_MIN;
	memset(vis, 0, sizeof(vis));
	State now(0, start);
	q.push(now);
	vis[now.node] = 1;
	while (!q.empty())
	{
		now = q.front();
		q.pop();
		step = max(step, now.step);
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
	return step;

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
	int ans = INT_MIN;
	for (int i = 1; i <= n + m; i++)
	{
		ans = max(ans, bfs(i));
	}
	cout << ans << endl;
}