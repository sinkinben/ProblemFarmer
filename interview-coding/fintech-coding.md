## Fintech Coding

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



## String to Decimal

**Description**

Implement a decimal class, which supports parsing from string (e.g 2.33) to decimal, and then realize the addition of two decimals.

Here we suppose that the precision is fixed.

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



## Big Integer Divide

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



