#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	if(n==1)
	{
		cout<<a[0]<<endl;
		return 0;
	}
	sort(a,a+n);
	int mid=n/2;
	int left=mid, right=mid;
	while(left>=0 && a[left]==a[mid])
		left--;
	while(right<n && a[right]==a[mid])
		right++;
	if(left-0+1 == n-1-right+1)
		cout<<a[mid]<<endl;
	else
		cout<<-1<<endl;
	
}


