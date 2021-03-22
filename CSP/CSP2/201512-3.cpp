/*
    90分版本
    画线不难
    难在填充，但是想到用递归就很简单了
    感觉自己做题真的进步了
    希望这次CSP能考得高一点
    2019/3/12 21:23

*/
#include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
#include<string.h>
#include<string>
#define MAXMN 102
using namespace std;
int m,n,q;  //row=n, col=m
char plot[MAXMN][MAXMN]={{0}};

void fillUp(int x,int y, char c)
{
    int i=n-1-y;
    int j=x;
    if(i==-1 || i==n || j==-1 || j==m)
        return;
    if(plot[i][j]=='+' || plot[i][j]=='-' || plot[i][j]=='|' || plot[i][j]==c)
        return;
    plot[i][j]=c;
    fillUp(x-1,y,c);
    fillUp(x+1,y,c);
    fillUp(x,y-1,c);
    fillUp(x,y+1,c);
}
void drawLine(int x1, int y1, int x2, int y2)
{
    int i1=n-1-y1, j1=x1;
    int i2=n-1-y2, j2=x2;
    if(i1==i2)
    {
        int i=i1;
        if(j1>j2)
            swap(j1,j2);
        //plot[i][j1]=plot[i][j2]='+';  //端点都是'+'？不是很确定
        for(int j=j1;j<=j2;j++)
        {
            if(plot[i][j]=='|')
                plot[i][j]='+';
            else
                plot[i][j]='-';
        }

    }
    else
    {
        if(i1>i2)
            swap(i1,i2);
        int j=j1;
        //plot[i1][j]=plot[i2][j]='+';
        for(int i=i1;i<=i2;i++)
        {
            if(plot[i][j]=='-')
                plot[i][j]='+';
            else
                plot[i][j]='|';
        }
    }
}
void print()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            cout<<plot[i][j];
        cout<<endl;
    }
    //cout<<endl;
}

int main()
{
    ios::sync_with_stdio(0);
    memset(plot,'.',sizeof(plot));
    cin>>m>>n>>q;
    cin.ignore();
    int t;
    int x1,y1,x2,y2;
    int x,y;
    char c;
    while(q--)
    {
        cin>>t;
        if(t==1)
        {
            cin>>x>>y;
            cin>>c;
            fillUp(x,y,c);
        }
        else
        {
            cin>>x1>>y1>>x2>>y2;
            drawLine(x1,y1,x2,y2);
        }
        //print();
    }
    print();
    return 0;
}

/*
................
...+--------+...
...|CCCCCCCC|...
...|CC+-----+...
...|CC|.........
...|CC|.........
...|CC|.........
...|CC|.........
...|CC|.........
...|CC+-----+...
...|CCCCCCCC|...
...+--------+...
................
*/
