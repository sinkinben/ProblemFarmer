#include<iostream>
#include<cstring>
#define MAXT 1000001
bool h[MAXT]={0}, w[MAXT]={0};
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    int n;
    cin>>n;
    int a,b;
    for(int i=0;i<n;i++)
    {
        cin>>a>>b;
        memset(h+a,1,b-a);
    }
    for(int i=0;i<n;i++)
    {
        cin>>a>>b;
        memset(w+a,1,b-a);
    }
    int ans=0;
    for(int i=0;i<MAXT;i++)
        ans+=h[i]&&w[i];
    cout<<ans<<endl;
}
