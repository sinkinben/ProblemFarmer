#include "leetcode.h"
#include <unordered_map>
#include <cassert>
#include <algorithm>
#define isDigital(x) (('0' <= (x)) && ((x) <= '9'))
#define isSign(x) (((x) == '+') || ((x) == '-') || ((x) == '*') || ((x) == '/'))
class Solution
{
public:
    unordered_map<char, int> cmp = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};
    int calculate(string s)
    {
        stack<int> numbers;
        stack<char> signs;
        int len = s.length();
        for (int i = 0; i < len; i++)
        {
            char x = s[i];
            if (isDigital(x))
            {
                int j = i;
                while (isDigital(s[j]))
                    j++;
                numbers.push(stoi(s.substr(i, j - i)));
                i = j - 1;
            }
            else if (isSign(x))
            {
                if (signs.empty() || (cmp[x] > cmp[signs.top()]))
                    signs.push(x);
                else
                {
                    while (!signs.empty() && cmp[x] <= cmp[signs.top()])
                        exec(numbers, signs);
                    signs.push(x);
                }
            }
            else if (x == '(')
            {
                int flag = 0;
                int j = i;
                do
                {
                    if (s[j] == '(')
                        flag++;
                    else if (s[j] == ')')
                        flag--;
                    j++;
                } while (flag != 0);
                numbers.push(calculate(s.substr(i + 1, j - 1 - i - 1)));
                i = j - 1;
            }
        }
        while (!signs.empty())
            exec(numbers, signs);
        assert(numbers.size() == 1);
        return numbers.top();
    }
    void exec(stack<int> &nums, stack<char> &signs)
    {
        int a, b, val;
        char op;
        op = signs.top(), signs.pop();
        b = nums.top(), nums.pop();
        a = nums.top(), nums.pop();
        switch (op)
        {
        case '+':
            val = a + b;
            break;
        case '-':
            val = a - b;
            break;
        case '*':
            val = a * b;
            break;
        case '/':
            val = a / b;
            break;
        default:
            assert(0);
        }
        nums.push(val);
    }
};
int main()
{
    string strs[] = {"1 + 1",
                     " 6-4 / 2 ",
                     "2*(5+5*2)/3+(6/2+8)",
                     "(2+6* 3+5- (3*14/7+2)*5)+3"};
    Solution sol;
    for (auto &s : strs)
        cout << sol.calculate(s) << endl;
}
