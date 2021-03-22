#include<bits/stdc++.h>
#define ctoi(c) ((c)-'0')
using namespace std;
//ISBN = 语言 -  出版社 - 图书编号 -  识别码
char isbn[14]={'\0'}; 
int main()
{
	cin>>isbn;
	cin.ignore();
	int res=0;
	int scale=1;
	res+=ctoi(isbn[0])*(scale++);
	
	for(int i=2;i<=4;i++)
		res+=ctoi(isbn[i])*(scale++);
	for(int i=6;i<=10;i++)
		res+=ctoi(isbn[i])*(scale++);
	res=res%11;
	if(ctoi(isbn[12]) == res || (res==10&&isbn[12]=='X'))
	{
		cout<<"Right"<<endl;
		return 0;
	}
	else
	{
		if(res==10)
			isbn[12]='X';
		else
			isbn[12]=res+'0';
		cout<<isbn<<endl;
		return 0;
	}
} 
