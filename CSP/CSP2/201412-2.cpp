#include<iostream>
#define print(a) cout<<(a)<<' '
using namespace std;
int n;
int a[501][501]={{0}};
int main()
{
	cin>>n;
	int i,j;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			cin>>a[i][j];
	
	int r=1,c=1;
	print(a[r][c]);
	while(!(r==n&&c==n))
	{
		//right
		if(c<n)
			print(a[r][++c]);
		else
			print(a[++r][c]);
		//left down
		while(c>1 && r<n)
			print(a[++r][--c]);
		//down
		if(r<n)
			print(a[++r][c]);
		else
			print(a[r][++c]);
		//right up
		while(r>1 && c<n)
			print(a[--r][++c]);
	}
}


