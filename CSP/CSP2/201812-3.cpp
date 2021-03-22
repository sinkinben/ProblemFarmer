#include<iostream>
#include<algorithm>
#include<sstream>
#include<vector>
#include<string.h>
#define MAX_N	100000
using namespace std;
/*
IP地址a3,a2,a1,a0要求：
0<=ai<=255
无前导0 
*/
/*
	得分：80 
	评测结果：错误 
*/
int n;
struct IP{
	union{
		unsigned char c_val[4];
		unsigned int i_val=0;
	};
	int len=0;
	bool operator < (const IP &ip) const
	{
		if(i_val < ip.i_val)
			return true;
		else if(i_val==ip.i_val && len<ip.len)
			return true;
		return false;
	}
	unsigned int minIP()
	{
		if(i_val==0)
			return 0;
		int mask = 0x80000000;
		mask = (mask>>(len-1));
		return i_val&mask;
	}
	unsigned int maxIP()
    {
        return (val)|(((uint32_t)(-1))>>(len));
    }
    
	void print()
	{
		for(int i=3;i>=1;i--)
			printf("%d.",c_val[i]);
		printf("%d/%d\n",c_val[0],i_val==0?0:len);
	}
};
vector<IP> ipv;
void replaceAll(string &source,string pattern, string target)
{
	int pos = source.find(pattern);
	while(pos!=-1)
	{
		source.replace(pos,pattern.length(),target);
		pos = source.find(pattern);
	}
}

vector<string> splitString(string &str)
{
    istringstream ss(str);
    string s;
    vector<string> res;
    while (ss >> s)
        res.push_back(s);
    return res;
}

IP standard(vector<string> &vs)
{
	IP ip;
	int len = vs.size();
	int k=3;
	for(int i=0;i<=3;i++)
		ip.c_val[k--]=stoi(vs[i]);
	ip.len = stoi(vs[4]);
	return ip;
}

IP omitSuffix(vector<string> &vs)
{
	IP ip;
	int len = vs.size();
	ip.len = stoi(vs.back());
	
	int k=3;
	for(int i=0;i<len-1;i++)
		ip.c_val[k--] = stoi(vs[i]);
	//XXX
//	ip.len = getIPLength(ip.i_val);
	return ip;	
} 

IP omitLength(vector<string> &vs)
{
	IP ip;
	int k=3;
	for(string s:vs)
		ip.c_val[k--] = stoi(s);
	ip.len = vs.size()*8;
//	cout<<ip.len<<endl;
	return ip; 
}

bool checkIP(unsigned int val, int len)
{
	int i=0;
	while( ((val>>i)&0x1)==0x0 )
		i++;
	 
}

int main()
{
//	IP ip;
//	ip.i_val = 0x00000000;
//	ip.len = 1;
//	printf("%8x, %8x\n",ip.minIP(),ip.maxIP()); 
//	ip.i_val = 0x80000000;
//	printf("%8x, %8x\n",ip.minIP(),ip.maxIP()); 

	
	ios::sync_with_stdio(0);
	cin>>n;
	while(n--)
	{
		string s;
		cin>>s;
		cin.ignore();
		bool haveLen = s.find("/")!=string::npos;
//		cout<<haveLen<<endl;
		replaceAll(s,"."," ");
		replaceAll(s,"/"," ");
		vector<string> vs=splitString(s);
		
		if(vs.size() == 5)	//标准型 
			ipv.push_back(standard(vs));
		else if(haveLen)	//省略后缀，但有长度
			ipv.push_back(omitSuffix(vs));
		else if(!haveLen)	//省略长度 
			ipv.push_back(omitLength(vs));
			
	}
	sort(ipv.begin(),ipv.end());
	for(int i=1;i<ipv.size();i++)
	{
		unsigned int maxa = ipv[i-1].maxIP();
		unsigned int mina = ipv[i-1].minIP();
		unsigned int maxb = ipv[i].maxIP();
		unsigned int minb = ipv[i].minIP();
		if(mina<=minb && maxb<=maxa)
			ipv.erase(ipv.begin()+i), i--; 
	}
	
	for(int i=1;i<ipv.size();i++)
	{
		if(ipv[i-1].len == ipv[i].len)
		{
			IP ip;
			IP ipa = ipv[i-1];
			IP ipb = ipv[i];
			ip.i_val = ipa.i_val;
			ip.len = ipa.len - 1;
				
			if(!checkIP(ip.i_val, ip.len) &&
			   min(ipa.minIP(), ipb.minIP())==ip.minIP() &&
			   max(ipa.maxIP(), ipb.maxIP())==ip.maxIP())
			{
				// i-1 i == ipa ipb
				// i-1 i i+1 == ip ipa ipb
				// i-1 i i+1 == ip ipc ...
				ipv.insert(ipv.begin()+i-1,ip);
				ipv.erase(ipv.begin()+i,ipv.begin()+i+2);
				if(i-1>=1)
					i-=2;
				else
					i-=1;
			}
		}
	}
	
	for(IP ip:ipv)
		ip.print();
	
}


