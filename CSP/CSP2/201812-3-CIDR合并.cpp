/**
 * 0分版本
 * 暂时没找到bug
 * 0分原因：开启了sync_with_stdio(0)，但是cin/cout和scanf/printf混用了
 */

#include<bits/stdc++.h>
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
using namespace std;
struct IP{
    union{
        uint32_t val=0;
        uint8_t group[4];
    };
    uint32_t len=0;
    bool operator < (const IP &ip) const
    {
        if(val<ip.val)
            return true;
        if(val==ip.val && len<ip.len)
            return true;
        return false;
    }
    string toString()
    {
        string s="";
        stringstream ss;
        for(int i=3;i>=0;i--)
        {
            ss<<(int)group[i];
            s+=ss.str()+".";
            ss.str("");
        }
        s.pop_back();
        ss<<len;
        s+="/"+ss.str();
        return s;
    }

    uint32_t max()
    {
        return (val)|(((uint32_t)(-1))>>(len));
    }

    uint32_t min()
    {
        uint32_t mask = (-1)<<(32-len);
        return (val)&(mask);
    }
};
list<IP> lip;
void replaceAll(string &source,const string &pattern, const string &target)
{
    int pos = source.find(pattern);
    while(pos!=-1)
    {
        source.replace(pos,pattern.length(),target);
        pos = source.find(pattern);
    }
}
list<string> splitString(const string &str)
{
    istringstream ss(str);
    string s;
    list<string> res;
    while (ss >> s)
        res.push_back(s);
    return res;
}

IP getIP1(list<string> &l)
{
    IP ip;
    string &len = l.back();
    ip.len = atoi(len.data());
    l.pop_back();
    int i=3;
    for(string &s:l)
        ip.group[i--]=atoi(s.data());
    return ip;
}
IP getIP2(list<string> &l)
{
    uint32_t len = l.size();
    IP ip;
    ip.len=len*8;
    int i=3;
    for(string &s:l)
        ip.group[i--]=atoi(s.data());
    return ip;
}
bool isValid(const IP &ip)
{
    uint32_t i=0;
    for(i=0;i<32;i++)
    {
        if( ( (ip.val>>i) & 0x1 ) == 0x1)
            break;
    }
    return (32-i)<=ip.len;
}
void print()
{
    for(IP &ip:lip)
        printf("%s %8x %8x\n",ip.toString().data(),ip.min(),ip.max());
    cout<<"\n\n"<<endl;
}
int main()
{
    string line;
    int n;
    cin>>n;
    cin.ignore();
    while(n--)
    {
        getline(cin,line);
        //cout<<line<<endl;
        if(line.find("/")!=string::npos)  //有len的
        {
            replaceAll(line,"."," ");
            replaceAll(line,"/"," ");
            list<string> ls=splitString(line);
            lip.push_back(getIP1(ls));
        }
        else
        {
            replaceAll(line,"."," ");
            list<string> ls=splitString(line);
            lip.push_back(getIP2(ls));
        }
    }
    lip.sort();

    //print();

    list<IP>::iterator pre=lip.begin(), cur=lip.begin();
    cur++;
    for(;cur!=lip.end();)
    {
        IP &a=*(pre);
        IP &b=*(cur);
        if(a.min()<=b.min() && b.max()<=a.max())
        {
            cur=lip.erase(cur);
        }
        else
            pre++, cur++;
    }

    //print();

    pre=cur=lip.begin();
    cur++;
    for(; cur!=lip.end();)
    {
        IP &a=*pre;
        IP &b=*cur;
        uint32_t amax = a.max();
        uint32_t amin = a.min();
        uint32_t bmax = b.max();
        uint32_t bmin = b.min();
        if(a.len==b.len && ( (amin<=bmin && bmin<=amax) || (bmin<=amin && amin<=bmax) ) )
        {
            IP c=a;
            c.len--;
            uint32_t minval=min(a.min(),b.min());
            uint32_t maxval=max(a.max(),b.max());
            if(isValid(c) && c.min()<=minval && maxval<=c.max())
            {
                //cout<<"clen="<<c.len<<endl;
                pre = lip.erase(pre);   //pre指向b
                pre = cur = lip.erase(cur); //pre,cur均指向a,b后的位置d
                lip.insert(cur,c);          //cur指向c的下一个d
                pre=cur;
                cur--, pre--, pre--;
                if(pre==lip.end())
                {
                    pre=lip.begin();
                    cur=pre;
                    cur++;
                }
                continue;
            }

        }
        pre++, cur++;
    }

    for(IP &ip:lip)
        cout<<ip.toString()<<endl;


}
