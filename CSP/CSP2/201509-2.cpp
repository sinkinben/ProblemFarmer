#include<iostream>
using namespace std;
int main()
{
	int y,d;
	cin>>y>>d;
	int hash[13]={-1,31,28,31,30,31,30,31,31,30,31,30,31};
	hash[2]+=(y%4==0&&y%100!=0)||(y%400==0);
	int mon=1,day=0;
	while(d)
	{
		d--;
		day++;
		if(day==hash[mon]+1)
			mon++, day=1;
	}
	cout<<mon<<endl;
	cout<<day<<endl;
}


