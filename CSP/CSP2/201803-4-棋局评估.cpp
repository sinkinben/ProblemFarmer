#include<iostream>
#define A (1)
#define B (2)
/** Alice X 1
 ** Bob O 2
 */
using namespace std;
int plat[3][3]= {{0}};
int T, zeroNum=0;
void init()
{
    zeroNum = 0;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            cin >> plat[i][j];
            zeroNum += (plat[i][j] == 0);
        }
    }
}
int check()
{
    for(int i=0; i<3; i++)
        if(plat[i][0] != 0 && plat[i][0] == plat[i][1] && plat[i][1] == plat[i][2])
            return plat[i][0];
    for(int j=0; j<3; j++)
        if(plat[0][j] != 0 && plat[0][j] == plat[1][j] && plat[1][j] == plat[2][j])
            return plat[0][j];
    if(plat[0][0] != 0 && plat[0][0] == plat[1][1] && plat[1][1] == plat[2][2])
        return plat[0][0];
    if(plat[0][2] != 0 && plat[0][2] == plat[1][1] && plat[1][1] == plat[2][0])
        return plat[0][2];
    return 0;
}
int dfs(int who)
{
    int flag = check();
    if(flag == A && who == B)
        return zeroNum + 1;
    if(flag == B && who == A)
        return -zeroNum - 1;
    if(zeroNum == 0)
        return 0;

    int i,j;
    int alicemax = INT_MIN;
    int bobmin = INT_MAX;
    int t;
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            if(plat[i][j] == 0)
            {
                plat[i][j] = who;
                zeroNum--;
                if(who == A)
                    t = dfs(B), alicemax = max(alicemax, t);
                else
                    t = dfs(A), bobmin = min(bobmin, t);
                plat[i][j] = 0;
                zeroNum++;
            }
        }
    }
    if(who == A)
        return alicemax;
    else
        return bobmin;

}
int main()
{
    ios::sync_with_stdio(0);
    cin>>T;
    while(T--)
    {
        init();
        cout<<dfs(A)<<endl;
    }

}
