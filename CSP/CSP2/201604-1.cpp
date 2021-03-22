#include<iostream>
#include<fstream>
using namespace std;
bool plat[15+1][10]={0};
bool block[4][4]={0};
int col;
struct Record{
	int x=-1, y=-1;
};
Record rec[4];
void init()
{
//	#define cin file
//	fstream file;
//	file.open("russia.txt");
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<10;j++)
			cin>>plat[i][j];
	}
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			cin>>block[i][j];
	cin>>col;

	for(int j=0;j<10;j++)
		plat[15][j]=true;
	int index=0;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
			if(block[i][j])
				rec[index].x=i, rec[index].y=j, index++;
	}
}
int main()
{
	init();
	int row=0;
	bool flag;
	col--;
	while(1)
	{
		flag=false;
		for(int i=0;i<4;i++)
		{
			if(plat[row+rec[i].x][col+rec[i].y])
			{
				flag=true;
				break;
			}
		}
		if(flag)
			break;
		row++;
	}
	row--;
	for(int i=0;i<4;i++)
		plat[row+rec[i].x][col+rec[i].y]=true;
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<10;j++)
		{
			cout<<plat[i][j]<<' ';
		}
		cout<<endl;
	}
}


