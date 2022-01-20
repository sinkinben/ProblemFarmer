## [leetcode] 基本计算器

本文题目：

+ [224.基本计算器](https://leetcode-cn.com/problems/basic-calculator)：加减法，括号，空格。
+ [227.基本计算器II](https://leetcode-cn.com/problems/basic-calculator-ii)：加减乘除，无括号，空格。
+ [772.基本计算器III](https://leetcode-cn.com/problems/basic-calculator-iii)：加减乘除，括号，空格。

题目 772 需要 Plus 会员，可以看[这里的博客](https://www.cnblogs.com/grandyang/p/8873471.html) 。

第三题是字节跳动线上夏令营的原题。

## 版本 1 ：只考虑个位数

**实现需求**

+ 有空格
+ 数字只考虑个位数
+ 无括号
+ 支持四则运算

**实现思路**

数据结构课上学过的栈算法，将数字与操作符分离入栈，同时利用一个 `map` 来记录操作符的优先级。只有当前操作符 `x` 优先级严格大于栈顶操作符优先级，才能进栈，否则需要先执行栈顶操作符。

**代码实现**

```cpp
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
        for (char x : s)
        {
            if (isDigital(x))  numbers.push(x - '0');
            else if (isSign(x))
            {
                while (!signs.empty() && cmp[x] <= cmp[signs.top()])
                    exec(numbers, signs);
                signs.push(x);
            }
        }
        while (!signs.empty())  exec(numbers, signs);
        assert(numbers.size() == 1);
        return numbers.top();
    }
    // exec 函数表示对栈顶操作符运算，该函数不会变
    void exec(stack<int> &nums, stack<char> &signs)
    {
        int a, b, val;
        char op;
        op = signs.top(), signs.pop();
        b = nums.top(), nums.pop();
        a = nums.top(), nums.pop();
        switch (op)
        {
            case '+': val = a + b; break;
            case '-': val = a - b; break;
            case '*': val = a * b; break;
            case '/': val = a / b; break;
            default: assert(0);
        }
        nums.push(val);
    }
};
```

## 版本 2 ：考虑任意位数字

**实现需求**

+ 有空格
+ 数字任意多位
+ 无括号
+ 支持四则运算

**实现思路**

遇见数字，继续往前扫描，直到遇到非数字，这一整个子串转换为一个 `int` .

**代码实现**

这样就能通过题目 227 啦~

```cpp
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
            while (isDigital(s[j]))  j++;
            numbers.push(stoi(s.substr(i, j - i)));
            i = j - 1;
        }
        else if (isSign(x))
        {
            while (!signs.empty() && cmp[x] <= cmp[signs.top()])
                exec(numbers, signs);
            signs.push(x);
        }
    }
    while (!signs.empty())  exec(numbers, signs);
    assert(numbers.size() == 1);
    return numbers.top();
}
```



## 版本 3 ：考虑括号

**实现需求**

+ 有空格
+ 数字任意多位
+ 带括号
+ 支持四则运算
+ 考虑负数

这样就是字节笔试题目啦。

**实现思路**

很明显，对于带括号的表达式 `1+2*(1+2*(3))` ，括号中是一个子表达式，同样要进行求值处理，显示需要采用递归做法。

那么现在需要解决的就是：当遇到 `'('` 时，找到该 `'('` 包围的子表达式。**需要使用括号匹配算法。**

**代码实现**

可以通过 224 ，估计 772 也行（没会员，穷）。

```cpp
int calculate(string s)
{
    stack<int> numbers;
    stack<char> signs;
    int len = s.length();
    // 考虑负数, e.g. "-111-(-222*2)"
    if (len > 0 && s[0] == '-') numbers.push(0);
    for (int i = 0; i < len; i++)
    {
        char x = s[i];
        if (isDigital(x))
        {
            int j = i;
            while (isDigital(s[j]))  j++;
            numbers.push(stoi(s.substr(i, j - i)));
            i = j - 1;
        }
        else if (isSign(x))
        {
            while (!signs.empty() && cmp[x] <= cmp[signs.top()])
                exec(numbers, signs);
            signs.push(x);
        }
        else if (x == '(')
        {
            int flag = 0;
            int j = i;
            do
            {
                if (s[j] == '(')  flag++;
                else if (s[j] == ')')  flag--;
                j++;
            } while (flag != 0);
            numbers.push(calculate(s.substr(i + 1, j - 1 - i - 1)));
            i = j - 1;
        }
    }
    while (!signs.empty())  exec(numbers, signs);
    assert(numbers.size() == 1);
    return numbers.top();
}
```

