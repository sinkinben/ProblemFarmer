#include<iostream>
#include<string.h>
#define MAX 52
using namespace std;
struct Coor {
	int x = -1, y = -1;
	Coor(int xx = -1, int yy = -1) :x(xx), y(yy) {}
};
int coorlen = 0;
int r, c;
int sx, sy;
int tx, ty;
char a[MAX][MAX] = { {0} };
bool b[MAX][MAX] = { {0} };
int answer = 0;
Coor coor[MAX*MAX];
void dfs(int x, int y, bool rec)
{
	if (x < 0 || x >= r || y < 0 || y >= c)
		return;
	if (a[x][y] == '#' || b[x][y])
		return;
	b[x][y] = true;
	if (rec)
		coor[coorlen++] = Coor(x, y);
	if (a[x][y] == '+' || a[x][y] == 'T' || a[x][y]=='S')
		dfs(x, y - 1, rec), dfs(x - 1, y, rec), dfs(x, y + 1, rec), dfs(x + 1, y, rec);
	else if (a[x][y] == '-')
		dfs(x, y - 1, rec), dfs(x, y + 1, rec);
	else if (a[x][y] == '|')
		dfs(x - 1, y, rec), dfs(x + 1, y, rec);
	else if (a[x][y] == '.')
		dfs(x + 1, y, rec);

}

int main()
{
	ios::sync_with_stdio(0);
	cin >> r >> c;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			cin >> a[i][j];
			if (a[i][j] == 'S')
				sx = i, sy = j;
			else if (a[i][j] == 'T')
				tx = i, ty = j;
		}
	}
	dfs(sx, sy, true);
	if (!b[tx][ty])
	{
		cout << "I'm stuck!" << endl;
		return 0;
	}

	for (int i = 0; i < coorlen; i++)
	{
		memset(b, 0, MAX*MAX);
		dfs(coor[i].x, coor[i].y, false);
		if (!b[tx][ty])
			answer++;
	}
	cout << answer << endl;
	
}


