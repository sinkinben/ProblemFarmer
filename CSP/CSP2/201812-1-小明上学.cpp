/**
 * [0,r) red
 * [r,r+g) green
 * [r+g,r+g+y) yellow
 */

#include<iostream>
using namespace std;
int r,y,g,n;
int main()
{
    ios::sync_with_stdio(0);
    cin>>r>>y>>g;
    cin>>n;

    int k,t;
    int ans=0;
    for(int i=0;i<n;i++)
    {
        cin>>k>>t;
        if(k==0 || k==1)
            ans+=t;
        else if(k==2)
            ans+=t+r;
    }
    cout<<ans<<endl;
    return 0;
}
