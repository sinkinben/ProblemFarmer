#include<bits/stdc++.h>
using namespace std;
int y=0,d=0;
int main()
{
	cin>>y>>d;
	bool leap=(y%4==0&&y%100!=0)||(y%400==0);
	int m=1;
	int day=0;
	while(d)
	{
		d-- ,day++;
		switch(m)
		{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				if(day==32)	
					day=1,m++;
				break;
			case 2:
				if(leap&&day==30)
					day=1,m=3;
				else if(!leap&&day==29)
					day=1,m=3;
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				if(day==31)
					day=1,m++;
				break;
					
		}
	}
	cout<<m<<'\n'<<day<<endl;
}
