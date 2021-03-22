
#include "leetcode.h"
class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> v(num+1,0);
        v[0]=0, v[1]=1, v[2]=1, v[3]=2;
        for(int i=4;i<=num;i++)
        {
            v[i]=v[i>>1]+(i&0x1);
        }
        return v;
    }
};

/*
[0,3]  0 1 1 2 [4,7]  1 2 2 3
[8,11] 1 2 2 3 [12,15]2 3 3 4
[16,19]1 2 2 3 [20,23]2 3 3 4
[24,27]2 3 3 4
*/