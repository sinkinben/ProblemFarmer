#include<iostream>
#include<bits/stdc++.h>
#define isLeap(y)	( ((y)%400==0) || ((y)%4==0 && (y)%100!=0) )
int table[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
using namespace std;
/*
没做出来
难点：按什么顺序打印答案
如果是遍历[s,t]里面的每一分钟，时间复杂度有点大。 
*/
struct Date{
	int year,month,day,hour,minute;
	void loadStr(string &S)
	{
		year = stoi(S.substr(0,4));
		month = stoi(S.substr(4,2));
		day = stoi(S.substr(6,2));
		hour = stoi(S.substr(8,2));
		minute = stoi(S.substr(10,2));
	}
	unsigned long long getUllVal(bool needYear)
	{
		string _year = to_string(year);
		string _month = to_string(month);
		string _day = to_string(day);
		string _hour = to_string(hour);
		string _minute = to_string(minute);
		if(_month.length()==1)	_month="0"+_month;
		if(_day.length()==1)	_day="0"+_day;
		if(_hour.length()==1)	_hour="0"+_hour;
		if(_minute.length()==1)	_minute="0"+_minute;
		if(needYear)	return stoull(_year+_month+_day+_hour+_minute); 
		return stoull(_month+_day+_hour+_minute);
	}
	void nextMinute()
	{
		table[2]=(isLeap(year)==true ? 29:28); 
		minute++;
		if(minute==60)
			minute=0, hour++;
		if(hour==24)
			hour=0, day++;
		if(day==table[month]+1)
			day=1, month++;
		if(month==13)
			month=1, year++;	
	}
	bool operator < (const Date &d) const
	{
		if(year < d.year)		return true;
		if(month < d.month)		return true;
		if(day < d.day)			return true;
		if(hour < d.hour)		return true;
		if(minute < d.minute)	return true;
		return false;
	}
	void print()
	{
		cout<<year<<month<<day<<hour<<minute<<' ';
	}
};
struct Crontab{
	string min,hour,day,mon,dow;
	string command;	
	bool judge(string &s)
	{
		
	}
};
unsigned long long n,s,t;
Date ds,dt;
int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>s>>t;
	string S=to_string(s);
	string T=to_string(t);
	ds.loadStr(S);
	dt.loadStr(T);

}


