/** 20�ְ汾
 *
 */


#include<iostream>
#include<cstring>
#include<algorithm>
int n;
using namespace std;
bool check(int a[], int b[])
{
    if(a[0] != ((b[0]+b[1])/2))
        return false;
    if(a[n-1] != (b[n-2]+b[n-1])/2)
        return false;
    for(int i=1;i<=n-2;i++)
    {
        if(a[i] != (b[i-1]+b[i]+b[i+1])/3)
            return false;
    }
    return true;
}
void print(int b[])
{
    for(int i=0;i<n;i++)
        cout<<b[i]<<" ";
    cout<<endl;
}
bool calc(int a[], int b[])
{
    b[1]=(a[0]*2-b[0]);
    if(b[1]==0)
        b[1]++;
    else if(b[1]<=-1)
        return false;
    for(int i=2;i<=n-2;i++)
    {
        b[i]=3*a[i-1]-b[i-1]-b[i-2];
        if(-1==b[i] || b[i]==0)
            b[i]=1;
        else if(b[i]<=-2)
            return false;
    }
    b[n-1]=(a[n-1]*2-b[n-2]);
    if(b[n-1]==0)
        b[n-1]=1;
    else if(b[n-1]<=-1)
        return false;
    return true;

}
int main()
{
    ios::sync_with_stdio(0);
    cin>>n;
    int a[n];
    int b[n];
    for(int i=0;i<n;i++)
        cin>>a[i];
    for(int i=1;i<=2*a[0];i++)
    {
        b[0]=i;
        if(!calc(a,b))
            continue;
        if(check(a,b))
        {
            print(b);
            break;
        }
    }
}
