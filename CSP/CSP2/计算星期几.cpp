#include<iostream>
using namespace std;
const char *weekday[7]={"Sunday","Monday","Tuesday","Wednesday",
				  		"Thursday","Friday","Saturday"};

int calcDayOfWeek(int y, int m, int d)
{
	//Sun=0, Mon=1, Tue=2, ...,
	//Sat=6
	int w;
	if(m==1||m==2)
		m+=12, y--;
	w=(d + 2*m + 3*(m+1)/5 + y + y/4 - y/100 + y/400 + 1)%7;
	return w;
}				  		
int main()
{
	ios::sync_with_stdio(0);
	int y,m,d;
	cin>>y>>m>>d;
	int w = calcDayOfWeek(y,m,d);
	printf("%s\n",weekday[w]);
}



