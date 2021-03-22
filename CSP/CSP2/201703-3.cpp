/*
	70�ְ汾
	�����˳����Ӻ�б��Ƕ�׵����
	������Ŀ�������������˵��
	�����ǰ����Լ������д��
	30�ִ���֪������ 
*/ 
#include<iostream>
#include<vector>
#include<fstream>
#include<string.h>
#define HEAD1_INDEX 2
#define HEAD2_INDEX 3
using namespace std;
vector<string> md(105);
static int mdlen=0;
char head1[]="<h1>", head2[]="</h1>";
char ul1[]="<ul>", ul2[]="</ul>";
char li1[]="<li>", li2[]="</li>";
char p1[]="<p>", p2[]="</p>";
char em1[]="<em>", em2[]="</em>";
void heading(string &line)
{
	int i=0;
	while(line[i]=='#')
		i++;
	int level = i;
	while(line[i]==' ')
		i++;
	head1[HEAD1_INDEX]=head2[HEAD2_INDEX]='0'+level;
	cout<<head1<<line.substr(i)<<head2<<endl; 
}
int ulist(int start)
{
	/*
	�ɻ��������3���Ƿ�ͬ����һ��ul?
		* 11111
		* 22222
		
		* 333333 
	*/
	int end = start;
	cout<<ul1<<endl;
	while(md[end].front() == '*')
		end++;
	
	for(int i=start;i<end;i++)
	{
		int j=1;
		while(md[i][j]==' ')
			j++;
		cout<<li1<<md[i].substr(j)<<li2<<endl;
	}
	cout<<ul2<<endl;
	return end-1;
}

int paragraph(int start)
{
	if(md[start].length() == 0)	//���У�ʲô������ 
		return start;
	int end=start;	//��endʹ��[start,end)����һ�� 
	while(md[end].length() != 0)
		end++;
	string content = "";
	for(int i=start;i<end;i++)
		content+=md[i]+"\n";
	content.pop_back();//ȥ����ӵ�һ��\n 
	
	for(int j=0;j<content.length();j++)
	{
		if(content[j]=='_')	//_italic_
		{
			content.replace(j,1,em1);
			j=j+strlen(em1)-1;
			j++;
			while(content[j]!='_')
				j++;
			content.replace(j,1,em2);
			j=j+strlen(em2)-1;
		}
	}
	
	for(int j=0;j<content.length();j++)
	{
		if(content[j]=='[') //[line](str)
		{
			int left=j;	//����[��λ�� 
			int i=j;
			while(content[j]!=']')
				j++;
			//substr[i->j] == "[text]"
			//substr[i+1->j-1] == "text"
			string text = content.substr(i+1,j-i-1);	
			j++;	//content[j]=='('
			i=j;
			while(content[j]!=')')
				j++;
			int right=j;	//)��λ�� 
			//substr[i->j] == "(link)"
			string link = content.substr(i+1,j-i-1);
			string output = "<a href=\""+link+"\">"+text+"</a>";
			content.replace(left,right-left+1,output);
			j = left+output.length()-1;
		}
	}
	
	cout<<p1<<content<<p2<<endl; 
	return end-1;
}

int main()
{
	ios::sync_with_stdio(0);
	string line;
	int linelen=0;
//	fstream file;
//	file.open("201703-3.txt");
//	#define cin file
	while(getline(cin,line))
		md[mdlen++]=line;
		
	for(int i=0;i<mdlen;i++)
	{
		char c = md[i].front();
		if(c == '#')
			heading(md[i]);
		else if(c == '*')
			i=ulist(i);
		else
			i=paragraph(i);		 
	}
}


