## Jump Trading 

Refer to:

- https://leetcode-cn.com/circle/discuss/Go8wIO/
- https://leetcode.com/discuss/interview-question/686727/Jump-Trading-or-Codility



## String to Rational Number

**Example**

```text
"3.14" -> 314/100；
"10/14" -> 10/14；
"5" -> 5
```

**Constraints**

- Define a class `Rational`.
- If the input string is not same as any format above, or the input is not a valid rational number, then we are required to output some error messages.
- You are ONLY allowed to scan the string **once** (from left to right).

**Solution**

- The rational numbers include **decimals** and **fractions**, which can be identified by `.` or `/` .
- Specially, the **integers** like `"5"` belong to fractions, and we stored integer in `fraction{num, 1}`.
- Pay attention to the **negative** numbers.
- **Leading-zeros is valid.**
  - e.g. `"0001.0" => {10, 10}`
- Here, we DO NOT consider reduction of fractions and fractions.
  - e.g. `"10.0" => {100, 10}`, `"10/5" => {10, 5}`.
  - If we consider the reduction of fractions, we should let `first /= gcd, second /= gcd`.

<br/>

```cpp
#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
class Rational {
private:
    enum Error { INVALID_INPUT, NON_DIGITAL, FRACTION_ZERO };
    unordered_map<Error, string> msgs = {
        {Error::INVALID_INPUT, " Invalid input."},
        {Error::NON_DIGITAL, " Contains non-digital letters."},
        {Error::FRACTION_ZERO, " Second part of fraction can not be zero."}
    };

public:
    bool isNegative;
    pair<uint32_t, uint32_t> value;

    Rational(const string &str) {
        setValue(str);
    }

    void setValue(const string &str) {
        /* initialization */
        isNegative = false;
        value = {0, 0};

        uint32_t first = 0, n = str.length(), i = 0;

        /* negative number */
        if (i < n && str[i] == '-')
            isNegative = 1, ++i;

        /* 1st part before '.' or '/' */
        while (i < n && isDigit(str[i]))
            first = first * 10 + (str[i] - '0'), ++i;

        /* parse number from the remained part. */
        auto parseNumber = [&str, this](uint32_t &val, uint32_t j) {
            int n = str.length();
            while (j < n) {
                if (!this->isDigit(str[j]))
                    throw str + msgs[Error::NON_DIGITAL];
                val = val * 10 + (str[j] - '0'), ++j;
            }
        };

        /* 2nd part after '.' or '/'
         * 1) i == n: input is an integer
         * 2) i == n-1: the last letter is non-digital, hence it's invalid
         */
        if (i == n)
            value = {first, 1};
        else if (i == n - 1)
            throw str + msgs[Error::INVALID_INPUT];
        else if (str[i] == '/') {
            uint32_t second = 0;
            parseNumber(second, i + 1);
            if (second == 0)
                throw str + msgs[Error::FRACTION_ZERO];
            value = {first, second};
        } else if (str[i] == '.') {
            parseNumber(first, i + 1);
            value = {first, (uint32_t)(pow(10, n - i - 1))};
        } else {
            /* after 1st number, the character must '.' or '/' */
            throw str + msgs[Error::INVALID_INPUT];
        }
    }

    bool isDigit(char ch) { return '0' <= ch && ch <= '9'; }

    virtual ~Rational() {}
};

void runTest(const string &str, pair<uint32_t, uint32_t> value, bool negative) {
    static int cnt = 0;
    Rational ration(str);
    assert(ration.isNegative == negative);
    assert(ration.value == value);
    printf("Pass %d: %s \n", ++cnt, str.c_str());
}

int main() {
    try {
        runTest("10000.0", {100000, 10}, false);
        runTest("3.14", {314, 100}, false);
        runTest("-3.14", {314, 100}, true);
        runTest("1000.1", {10001, 10}, false);
        runTest("10.1999292", {101999292, pow(10, 7)}, false);
        runTest("-10.1999292", {101999292, pow(10, 7)}, true);
        runTest("7/3", {7, 3}, false);
        runTest("-10/5", {10, 5}, true);
        // runTest("-a.3", {0, 0}, true);
        // runTest("10001a", {0, 0}, false);
        // runTest("10a01", {10, 1}, false);
        // runTest("abc", {0, 0}, false);
    } catch (const string &msg) {
        cerr << msg << '\n';
    }
}
```



## File Iterator

A file contains a sequence of integers, stored one per line. Implement a class that facilitates iteration over these integers.

A valid integer is a sequence of one or more digits (without leading-zeros), optionally preceded by a plus or minus sign, representing a number within the range `[-1e9, 1e9]`. We allow spaces to appear in a line before and/or after a valid integers. Lines are separated with the line-feed character (ASCII code 10).

There might be lines that do not represent valid integers, e.g. `2u1, 23.9, #12, 00, ++1, 20`. Such lines are considered to comments, and should be discarded.

Define a class `Solution` with an input iterator (as defined by C++03 and 11) that iterates over integers from an input stream compliant with the above format.

You should implement the following interfaces:

```cpp
#include <iosfwd>
class Solution {
public:
    Solution(istream &s);
    class iterator;
    iterator begin();
    iterator end();
};
/**
 * Example usage:
 *     Solution sol(stream);
 *     for (Solution::iterator it = sol.begin(); it != sol.end(); ++it) {
 *         int x = *it;
 *         cout << x << endl;
 *     }
 */
```

<br/>

**Solution**

The first problem we need to solve is to construct an `istream` object from a file `nums.txt`.

```cpp
int main()
{
    filebuf file;

    if (file.open("./nums.txt", ios::in) == nullptr) {
        cout << "Open file failed.\n";
        exit(EXIT_FAILURE);
    }

    istream input(&file);
    string buf;
    while (getline(input, buf))
        cout << buf << endl;
}
```

Here is my code.

```cpp
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <regex>
using namespace std;

class Solution {
public:
    class iterator {
    public:
        iterator(istream &stream, bool end = false) : input(stream) {
            memset(value, 0, sizeof(value));
        }

        iterator(const iterator &it) : input(it.input) {
            memcpy(value, it.value, sizeof(value));
        }

        /* (*itor) */
        int operator*() const {
            string str(value);
            return stoi(str);
        }

        /* (++itor) */
        iterator &operator++() {
            do {
                if (input.eof())
                    break;
                input.getline(value, sizeof(value));
            } while (!validNumber(value));
            return *this;
        }

        bool validNumber(char *str) {
            static regex pattern("(\\s*)([+-]?)([1-9]\\d*|0)(\\s*)");
            static const char *MAXVAL = "1000000000";

            if (!regex_match(str, pattern))
                return false;

            /* remove leading spaces */
            while (*str == ' ')
                ++str;
            str += (str[0] == '+') || (str[0] == '-');

            /* remove trailing spaces */
            int n = strlen(str);
            while (str[n - 1] == ' ')
                --n;
            str[n] = '\0';

            return (n < 10) || (n == 10 && strcmp(str, MAXVAL) == 0);
        }

        /* dummy end iterator */
        bool operator!=(const iterator &itor) const { return !input.eof(); }

    protected:
        istream &input;
        char value[256];
    };

public:
    Solution(istream &stream) : input(stream) {}

    iterator begin() {
        iterator it(input);
        ++it;
        return it;
    }

    iterator end() { return iterator(input); }

protected:
    istream &input;
};

int main() {
    filebuf file;

    if (file.open("./nums.txt", ios::in) == nullptr) {
        cout << "Open file failed.\n";
        exit(EXIT_FAILURE);
    }

    istream input(&file);

    Solution sol(input);

    for (auto it = sol.begin(); it != sol.end(); ++it) {
        cout << *it << endl;
    }
}
```

Here is my test `nums.txt`. Please note that there must be an empty line at the end of file.

```text
1  
  +11111  
  -101000  
  12312   
2131.11  
    1000000000  
    999999999
  1000000001   
      2000000000
  +0   
   -0    
    0111  
    #1123411
    ++1
 abc
289

```



## Decimal

**Description**

Implement a decimal class, which supports parsing from string (e.g 2.33) to decimal, and then realize the addition of two decimals.

<br/>

**Solution**

```cpp
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

class Decimal {
  protected:
    uint64_t value;
    /* there are at most 10 numbers after '.' */
    const int precision = 10;

  public:
    Decimal(const string &str) { setValue(str); }

    void setValue(const string &str) {
        value = 0;
        int n = str.length();
        int point = n;
        for (int i = 0; i < n; ++i) {
            if ('0' <= str[i] && str[i] <= '9')
                value = value * 10 + (str[i] - '0');
            else if (str[i] == '.')
                point = i;
        }
        for (int i = n - point; i <= precision; ++i)
            value = value * 10;
    }

    Decimal &operator+=(const Decimal &decimal) {
        value += decimal.value;
        return *this;
    }

    bool operator==(const Decimal &decimal) const {
        return value == decimal.value;
    }

    void display() {
        string str = to_string(value);
        int pos = str.length() - precision;
        str.insert(pos, 1, '.');
        cout << str << "\n";
    }
};

int main() {
    Decimal d("1.11111");
    d += Decimal("2.9999999");
    d.display();
}
```



## Divide

Given `string a` and integer `int b`, output `a / b` and `a % b`.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
// A除b  r为余数
vector<int> div(vector<int> &A, int b, int &r) {
    vector<int> C;
    r = 0;
    for (int i = 0; i < A.size(); ++i) {
        r = r * 10 + A[i];
        C.push_back(r / b);
        r = r % b;
    }
    // 存储顺序逆转
    reverse(C.begin(), C.end());
    // 处理前导0
    while (C.size() > 1 && C.back() == 0)
        C.pop_back();
    reverse(C.begin(), C.end());
    return C;
}

int main() {
    string a = "12345";
    int b = 11;

    vector<int> A;
    for (char x : a)
        A.emplace_back(x - '0');

    int r; //存储余数
    vector<int> C = div(A, b, r);
    for (int x : C)
        cout << x;
    cout << endl << r << endl;

    return 0;
}

```



## References

- [1] http://arzhon.blog.binusian.org/oop-rational-class-in-cpp/
