#include <cstdio>
#include <deque>
#include <cassert>
#include <cmath>
#define ALICE 1
#define BOB 2
struct Coor
{
    int x, y;
    Coor(int xx = -1, int yy = -1) : x(xx), y(yy) {}
};
using namespace std;
int a[3][3] = {{0}};
int zeros = 0;
void input()
{
    zeros = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &a[i][j]);
            if (a[i][j] == 0)
            {
                zeros++;
            }
        }
    }
}
int check()
{
    for (int i = 0; i < 3; i++)
    {
        if (a[i][0] != 0 && a[i][0] == a[i][1] && a[i][1] == a[i][2])
            return a[i][0];
    }
    for (int j = 0; j < 3; j++)
    {
        if (a[0][j] != 0 && a[0][j] == a[1][j] && a[1][j] == a[2][j])
            return a[0][j];
    }
    if (a[0][0] != 0 && a[0][0] == a[1][1] && a[1][1] == a[2][2])
        return a[0][0];
    if (a[0][2] != 0 && a[0][2] == a[1][1] && a[1][1] == a[2][0])
        return a[0][2];
    return -1;
}
int solve(int who)
{
    int flag = check();
    if (flag == -1)
    {
        if (zeros == 0)
            return 0;
    }
    else
    {
        if (who == ALICE && flag == BOB)
            return -zeros - 1;
        if (who == BOB && flag == ALICE)
            return zeros + 1;
    }
    int alice = -1, bob = 0x7fffffff;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (a[i][j] == 0)
            {
                a[i][j] = who, zeros--;
                if (who == ALICE)
                {
                    alice = max(alice, solve(bob));
                }
                else if (who == BOB)
                {
                    bob = min(bob, solve(alice));
                }
                a[i][j] = 0, zeros++;
            }
        }
    }
    if (who == ALICE)
        return alice;
    else if (who == BOB)
        return bob;

}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        input();
        printf("%d\n", solve(ALICE));
    }
}