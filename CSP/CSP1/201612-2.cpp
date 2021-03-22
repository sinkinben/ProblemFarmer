#include<bits/stdc++.h>
using namespace std;
int after=0;
int main()
{
	cin>>after;
	if(after<=3500)
	{
		cout<<after<<endl;
		return 0;
	}
	for(int before=100;before<=100000;before+=100)
	{
		int A=before-3500;
		if (A<=1500)
		{
			if((int)(before - A*0.03) == after)
			{
				cout<<before<<endl;
				return 0;
			}
		}
		else if(A<=4500)
		{
			if((int)(before - 45 - (A-1500)*0.1) == after)
			{
				cout<<before<<endl;
				return 0;
			}
		}
		else if(A<=9000)
		{
			if((int)(before - 45 - 300 - (A-4500)*0.2) ==  after)
			{
				cout<<before<<endl;
				return 0;
			}
		}
		else if(A<=35000)
		{
			if((int)(before - 45 - 300 - 900 - (A-9000)*0.25) ==  after)
			{
				cout<<before<<endl;
				return 0;
			}
		}
		else if(A<=55000)
		{
			if((int)(before - 1245 - 6500 - (A-35000)*0.3) == after)
			{
				cout<<before<<endl;
				return 0;
			}
		}
		else if(A<=80000)
		{
			if((int)(before - 7745 - 6000 - (A-55000)*0.35) == after)
			{
				cout<<before<<endl;
				return 0;
			}
		}
		else if(A>80000)
		{
			if((int)(before - 13745 - 8750 - (A-80000)*0.45) == after)
			{
				cout<<before<<endl;
				return 0;
			}
		}
		
	}
}
