#include "leetcode.h"
/*
    偶数必胜
    可以知道，当 2 落在谁手上，谁就胜利
    偶数的因子可以是奇数，也可以是偶数（1也是因子）
    奇数的因子必然是奇数
    如果 n 是偶数：
        alice一直取 1 ，当回到alice手上时，n仍是偶数，边界是 2 
    如果 n 是奇数：
        alice开始无论怎么取，都会把一个偶数交给bob，这样就是bob必胜
 */
class Solution
{
public:
    bool divisorGame(int N)
    {
        return (N % 2) == 0;
    }
};