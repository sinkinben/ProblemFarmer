#include<iostream>
#include<cstdio>
#include<algorithm>
#define RIGHT (1)
#define LEFT (-1)
struct Ball
{
    int order = 0;
    int dir = RIGHT;
    int pos = -1;
    void rev_dir() { dir = (dir == RIGHT)? LEFT: RIGHT;}
};
using namespace std;
int n,L,t;
Ball ball[101];
void mov()
{
    for(int i=0;i<n;i++)
    {
        ball[i].pos+=ball[i].dir;
    }
    if(ball[0].pos==0)
        ball[0].dir = RIGHT;
    for(int i=0;i<=n-2;i++)
    {
        if(ball[i].pos == ball[i+1].pos)
        {
            ball[i].rev_dir();
            ball[i+1].rev_dir();
            i++;
        }
    }
    if(ball[n-1].pos==L)
        ball[n-1].dir = LEFT;
}
bool cmp1(Ball &b1, Ball &b2) { return b1.pos < b2.pos; }
bool cmp2(Ball &b1, Ball &b2) { return b1.order < b2.order; }

int main()
{
    scanf("%d %d %d", &n, &L, &t);
    for(int i=0;i<n;i++)
    {
        ball[i].order = i+1;
        cin>>ball[i].pos;
    }
    sort(ball,ball+n,cmp1);
    while(t--)
        mov();
    sort(ball,ball+n,cmp2);
    for(int i=0;i<n;i++)
        cout<<ball[i].pos<<' ';

}
