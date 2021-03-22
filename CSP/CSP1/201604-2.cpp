#include<bits/stdc++.h>
#define checkBRow(i)	(!(b[i][0]==0 && b[i][1]==0 && b[i][2]==0 && b[i][3]==0))
using namespace std;
bool a[15][10];
bool b[4][4];
int c[4]={0};
int k=0;
void print()
{
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<10;j++)
			cout<<a[i][j]<<' ';
		cout<<endl;
	}
	cout<<endl;
}
int main()
{
//	fstream file;
//	file.open("201604-2.txt");
//	#define cin file

	for(int i=0;i<15;i++)
	{
		for(int j=0;j<10;j++)
		{
			cin>>a[i][j];
		}
	}
		
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			cin>>b[i][j];
			c[j]+=b[i][j];
		}
	}
	cin>>k;
	k--;
	
	int row1,row2;
	for(int i=0;i<4;i++)
	{
		if(checkBRow(i))
		{
			row1=i;
			break;
		}
	} 
	for(int i=3;i>=row1;i--)
	{
		if(checkBRow(i))
		{
			row2=i;
			break;
		}
	}
	
	for(int j=k;j<=k+3;j++)
	{
		for(int i=0;i<15;i++)
		{
			if(a[i][j])
			{
				c[j-k]+=15-i;
				break;
			}
		}
	}
	
	int mcol=0, mrow;
	for(int i=1;i<4;i++)
	{
		if(c[i]>c[mcol])
			mcol=i;
	}
	//k , k+1, k+2, k+3
	//0, 1, 2, 3 
	mcol+=k;
	for(int i=0;i<=13;i++)
	{
		if(!a[i][mcol] && a[i+1][mcol])
		{
			mrow=i;
			break;
		}
	}
	int movedown=0;
	if(b[row2][mcol-k])
		movedown=0;
	else
	{
		int t=row1;
		while(b[t][mcol-k])
			t++;
		movedown=row2-t+1;
	}
	cout<<"movedown="<<movedown<<endl;
	cout<<"row1="<<row1<<' '<<"row2="<<row2<<endl;
	
	int h=row2-row1+1;
	int r=row1;
	for(int i=mrow-h+1+movedown;i<=mrow+movedown;i++)
	{
		for(int j=k;j<=k+3;j++)
		{
			if(!a[i][j] && b[r][j-k])
				a[i][j]=true;
			else if (a[i][j]&&b[r][j-k])
				assert(0);
		}
		r++;
	}
	
	print();
	
}
