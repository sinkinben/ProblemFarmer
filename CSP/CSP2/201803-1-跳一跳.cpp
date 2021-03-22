#include<iostream>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    int n;
    int ans=0;
    int points=2;
    while(cin>>n && n!=0)
    {
        if(n==1)
            ans++, points=2;
        else if (n==2)
            ans+=points, points+=2;
    }
    cout<<ans<<endl;
    return 0;
}
