#include<bits/stdc++.h>
using namespace std;
int a[1005]={0};
int main()
{
    ios::sync_with_stdio(0);
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>a[i];
    cout<<(a[0]+a[1])/2<<' ';
    for(int i=1;i<=n-2;i++)
        cout<<(a[i-1]+a[i]+a[i+1])/3<<" ";
    cout<<(a[n-2]+a[n-1])/2<<endl;

}
