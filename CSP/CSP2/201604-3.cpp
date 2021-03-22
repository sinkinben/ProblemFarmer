/*
90�ְ汾
״̬���ã�˼·�������д�����debugҲ��
û����ȫ��
*/

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<stack>
#include<sstream>
using namespace std;
int p;
string curPath;
vector<string> path;
void replaceAll(string &source,string pattern, string target)
{
    int pos = source.find(pattern);
    while(pos!=-1)
    {
        source.replace(pos,pattern.length(),target);
        pos = source.find(pattern);
    }
}
vector<string> splitString(const string &str)
{
    istringstream ss(str);
    string s;
    vector<string> res;
    while (ss >> s)
        res.push_back(s);
    return res;
}
void print(vector<string> &ans)
{
    if(ans.empty())
    {
        cout<<"/"<<endl;
        return;
    }
    int vsize = ans.size();
    for(int i=0; i<vsize; i++)
        cout<<"/"<<ans[i];
    cout<<endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin>>p;
    cin>>curPath;
    cin.ignore();
    replaceAll(curPath,"/"," ");
    path = splitString(curPath);
    string s;
    while(p--)
    {
        s.clear();
        getline(cin,s); //s�п����ǿմ���������getline
        if(s=="")
        {
            print(path);
            continue;
        }
        if(s.find(".")==-1) //û��.
        {
            s.erase(unique(s.begin(),s.end()),s.end());
            if(s.length()>1 && s.back()=='/')
                s.pop_back();
            cout<<s<<endl;
            continue;
        }
        //���涼����.
        vector<string> ans;
        if(s.front()!='/')
            ans.insert(ans.begin(),path.begin(),path.end());
        replaceAll(s,"/"," ");
        vector<string> vs = splitString(s);
        int vsize = vs.size();
        for(int i=0; i<vsize; i++)
        {
            if(vs[i]!=".." && vs[i]!=".")
                ans.push_back(vs[i]);
            else if(vs[i]==".." && !ans.empty())
                ans.pop_back();
        }
        print(ans);

    }
}
/*
10
/d2/d3
/d1/../../d2
/d2/d4/f1
../d4/f1
/d1/./f1
/d1///f1
/d1/
///
/../../.././../.

////////////
*/
