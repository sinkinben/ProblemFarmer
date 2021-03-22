#include<iostream>
#include<algorithm>
#define MAXLEN 1001
using namespace std;
struct Box {
	int num;
	int times;
	Box(int nn = -1, int tt = 0) :num(nn), times(tt) {}
	bool operator < (const Box &b) const {
		if (times > b.times)
			return true;
		else if (times == b.times && num < b.num)
			return true;
		return false;
	}
};
int n;
Box box[MAXLEN];
int main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 0; i < MAXLEN; i++)
		box[i].num = i;
	int t;
	while (n--)
	{
		cin >> t;
		box[t].times++;
	}
	sort(box, box + MAXLEN);
	for (int i = 0; i < MAXLEN; i++)
	{
		if (box[i].times)
		{
			cout << box[i].num << ' ' << box[i].times << endl;
		}
	}
}