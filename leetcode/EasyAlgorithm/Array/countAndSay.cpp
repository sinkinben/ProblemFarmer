class Solution {
public:
    string countAndSay(int n) {
        if (n == 0) return "";
        string s = "1";
        string buf="";
        for (;n>1; n--)
        {
            int len = s.length();
            for (int i=0; i<len;)
            {
                char c = s[i];
                int j = i;
                while (j < len && s[j] == c)
                    j++;
                buf += (j-i)+'0';
                buf += c;
                i=j;
            }
            // cout<<buf<<endl;
            s = buf;
            buf = "";
        }
        return s;

    }
};
