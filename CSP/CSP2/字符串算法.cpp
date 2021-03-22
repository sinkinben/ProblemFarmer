#include<iostream>
#include<bits/stdc++.h>
#include<string> 
#include<string.h>
using namespace std;
void replaceAll(string &source,string pattern, string target)
{
	int pos = source.find(pattern);
	while(pos!=-1)
	{
		source.replace(pos,pattern.length(),target);
		pos = source.find(pattern);
	}
}

int main()
{
	string s = "2323 string";
//	replaceAll(s,"3 ",""); 
//	cout<<(s.find("sss")==string::npos); 

//	char str[]="i,am,a,hape*sin*fuck";
//	char *p = strtok(str,",*");
//	while(p)
//	{
//		printf("%s\n",p);
//		p=strtok(NULL,",*");
//	}

	//Êý×ÖÓë×Ö·û´®×ª»»
//	int i=123;
//	float f=123.0;
//	cout<<to_string(i)<<endl;
//	cout<<to_string(f)<<endl;
//	string numstr = "2333";
//	int num = stoi(numstr);

//	transform(s.begin(),s.end(),s.begin(),::toupper);
//	cout<<s<<endl;
//	transform(s.begin(),s.end(),s.begin(),::tolower);
//	cout<<s;

	//stod stof stoi
	//stoll stoull
	string t[]={"3.14159", "3.14", "3",
			    "-123546798", "-123456789",
				};
	printf("%f\n%f\n%d\n%lld\n%llu\n",
		  stod(t[0]),
		  stof(t[1]),
		  stoi(t[2]),
		  stoll(t[3]),
		  stoull(t[4]));
	 

}


