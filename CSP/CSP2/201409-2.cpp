#include<bits/stdc++.h>
using namespace std;
bool plat[101][101]={{0}};
int main()
{
	int n;
	cin>>n;
	cin.ignore();
	int x1,x2,y1,y2;
	while(n--)
	{
		cin>>x1>>y1>>x2>>y2;
		cin.ignore();
		for(int i=x1;i<x2;i++)
			for(int j=y1;j<y2;j++)
				plat[i][j]=true;
	}
	int ans=0;
	for(int i=0;i<101;i++)
		for(int j=0;j<101;j++)
			ans+=plat[i][j];
	cout<<ans<<endl;
}

