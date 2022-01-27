## Basic Calculator

Problems:

- [224. Basic Calculator](https://leetcode.com/problems/basic-calculator/)
- [227. Basic Calculator II](https://leetcode.com/problems/basic-calculator-ii)
- [772. Basic Calculator III](https://leetcode.com/problems/basic-calculator-iii)
- [770. Basic Calculator IV](https://leetcode.com/problems/basic-calculator-iv)



## Calculator

**Constraints:**

- `1 <= s.length <= 3 * 105`
- `s` consists of digits, `'+'`, `'-'`, `'('`, `')'`, and `' '`.
- `s` represents a valid expression.
- `'+'` is **not** used as a unary operation (i.e., `"+1"` and `"+(2 + 3)"` is invalid).
- `'-'` could be used as a unary operation (i.e., `"-1"` and `"-(2 + 3)"` is valid).
- There will be no two consecutive operators in the input.
- Every number and running calculation will fit in a signed 32-bit integer.

Since there are only two `+, -` operators, we can compute the result from left to right.

- Use `op` to record the latest operator we have meet.
- When meet `'('`, get index of `')'` that matches. Process the sub-expression in a recursion way.

```cpp
class Solution 
{
public:
    int calculate(string s) { return calc(s); }
    
    bool isdigit(char x) { return '0' <= x && x <= '9'; }

    int compute(int basic, char op, int val) { return op == '+' ? basic + val : basic - val; }
    
    int calc(string &s)
    {
        int n = s.length(), res = 0, i = 0;
        char op = '+';
        while (i < n && s[i] == ' ') i++;
        
        if (i < n && s[i] == '-') op = '-';
        
        for (; i < n; ++i)
        {
            if (s[i] == '+' || s[i] == '-') op = s[i];
            else if (s[i] == '(')
            {
                int j = i, cnt = 0;
                do 
                {
                    cnt += (s[j] == '(');
                    cnt -= (s[j] == ')');
                    j += 1;
                } while (cnt != 0);
                string sub = s.substr(i + 1, j - i - 2);
                res = compute(res, op, calc(sub));
                i = j - 1;
            }
            else if (isdigit(s[i]))
            {
                int j = i, val = 0;
                while (j < n && isdigit(s[j]))
                    val = val * 10 + (s[j] - '0'), j += 1;
                res = compute(res, op, val);
                i = j - 1;
            }
        }
        return res;
    }
};
```



## Calculator II

**Constraints:**

- `s` consists of integers and operators `('+', '-', '*', '/')` separated by some number of spaces.
- All the integers in the expression are non-negative integers in the range `[0, 2^31 - 1]`.
- There is no round brackets `()`.

```cpp
class Solution 
{
public:
    unordered_map<char, int> table = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};
    
    int calculate(string s) { return calc(s); }
    
    bool isdigit(char x) { return '0' <= x && x <= '9'; }
    
    void popStk(stack<int> &nums, stack<char> &ops)
    {
        int a, b, op;
        b = nums.top(), nums.pop();
        a = nums.top(), nums.pop();
        op = ops.top(), ops.pop();
        if (op == '+') nums.push(a + b);
        if (op == '-') nums.push(a - b);
        if (op == '*') nums.push(a * b);
        if (op == '/') nums.push(a / b);
    }
    
    int calc(string &s)
    {
        stack<int> nums;
        stack<char> ops;
        int n = s.length();
        for (int i = 0; i < n; ++i)
        {
            char x = s[i];
            if (table.count(x))
            {
                while (!ops.empty() && table[ops.top()] >= table[x])
                    popStk(nums, ops);
                ops.push(x);
            }
            else if (isdigit(x))
            {
                int j = i, val = 0;
                while (j < n && isdigit(s[j]))
                    val = val * 10 + (s[j] - '0'), j += 1;
                nums.push(val);
                i = j - 1;
            }
        }
        while (!ops.empty()) popStk(nums, ops);
        return nums.top();
    }
};
```



## Calculator III

Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, `'+', '-', '*', '/'` operators, and open `'('` and closing parentheses `')'`. The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of `[-2^31, 2^31 - 1]`.

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as `eval()`.

**Constraints:**

- `1 <= s <= 10^4`
- `s` consists of digits, `'+', '-', '*', '/', '('`, and `')'`.
- `s` is a valid expression.

**Example**

```
Input: s = "2*(5+5*2)/3+(6/2+8)"
Output: 21
```

<br/>

**Solution**

```cpp
class Solution 
{
public:
    unordered_map<char, int> table = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};
    
    int calculate(string s) { return calc(s); }
    
    bool isdigit(char x) { return '0' <= x && x <= '9'; }
    
    void popStk(stack<int> &nums, stack<char> &ops)
    {
        int a, b, op;
        b = nums.top(), nums.pop();
        a = nums.top(), nums.pop();
        op = ops.top(), ops.pop();
        if (op == '+') nums.push(a + b);
        if (op == '-') nums.push(a - b);
        if (op == '*') nums.push(a * b);
        if (op == '/') nums.push(a / b);
    }
    
    int calc(string &s)
    {
        stack<int> nums;
        stack<char> ops;
        int n = s.length(), i = 0;
        
        while (i < n && s[i] == ' ') i++;
        
        if (i < n && s[i] == '-') nums.push(0);
        
        for (; i < n; ++i)
        {
            char x = s[i];
            if (table.count(x))
            {
                while (!ops.empty() && table[ops.top()] >= table[x])
                    popStk(nums, ops);
                ops.push(x);
            }
            else if (isdigit(x))
            {
                int j = i, val = 0;
                while (j < n && isdigit(s[j]))
                    val = val * 10 + (s[j] - '0'), j += 1;
                nums.push(val);
                i = j - 1;
            }
            else if (x == '(')
            {
                int j = i, cnt = 0;
                do
                {
                    cnt += s[j] == '(';
                    cnt -= s[j] == ')';
                    j += 1;
                } while (cnt != 0);
                string sub = s.substr(i + 1, j - 2 - i);
                nums.push(calc(sub));
                i = j - 1;
            }
        }
        while (!ops.empty()) popStk(nums, ops);
        return nums.top();
    }
};
```



## Calculator IV

It seems that everybody dislikes this problem, so I decide to give up.