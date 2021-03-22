#include<bits/stdc++.h>
#define char2int(c) (c-'0')
using namespace std;
char isbn[13]={0};
int main()
{
	ios::sync_with_stdio(0);
	cin>>isbn;
	cin.ignore();
	
	int flag=0;
	int coe=1;
	flag=(flag+char2int(isbn[0])*coe)%11, coe++;
	for(int i=2;i<=4;i++)
		flag=(flag+char2int(isbn[i])*coe)%11, coe++;
	for(int i=6;i<=10;i++)
		flag=(flag+char2int(isbn[i])*coe)%11, coe++;

	int last=char2int(isbn[12]);
	if(flag == last || (flag==10 && isbn[12]=='X'))
		printf("Right\n");
	else
	{
		if(flag==10)
			isbn[12]='X';
		else 
			isbn[12]=flag+'0';
		printf("%s\n",isbn);
	}
	return 0;
	
}
