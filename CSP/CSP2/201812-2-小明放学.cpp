/** [0,r) red
 *  [r,r+g) green
 *  [r+g,r+g+y) yellow
 */

#include<bits/stdc++.h>
using namespace std;
int r,y,g,n;
int main()
{
    ios::sync_with_stdio(0);
    cin>>r>>y>>g;
    cin>>n;
    int k,t;
    int p;
    const int mod=r+y+g;
    unsigned long long ans=0;
    while(n--)
    {
        cin>>k>>t;
        if(k==0)
        {
            ans+=t;
            continue;
        }
        if(k==1)
            p=(r-t-1+ans)%mod;  //ÊÇ·ñ-1£¿
        else if(k==2)
            p=(r+y+g-t-1+ans)%mod;
        else if(k==3)
            p=(r+g-t-1+ans)%mod;
        if(0<=p && p<r)
            ans+=(r-p-1);
        else if(r+g<=p && p<r+g+y)
            ans+=(r+g+y-p-1)+r;
    }
    cout<<ans<<endl;
}
