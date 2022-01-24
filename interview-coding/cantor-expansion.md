## Cantor Expansion

Before we introduce the **Cantor Expansion**, let me show you a problem.

Given a group of numbers, such as `nums = [1, 2, 3]`, it will has `3! = 6` different permutations. And we sort it in lexicographical order, then each of these permutations will have an **unique index**. That is:

```text
idx     sequence
 0   :  [1, 2, 3]
 1   :  [1, 3, 2]
 2   :  [2, 1, 3]
 3   :  [2, 3, 1]
 4   :  [3, 1, 2]
 5   :  [3, 2, 1]
```

Now, we have 2 problems:

- Given `n`, and a sequence `nums[0, ..., n - 1]`, and `1 <= nums[i] <= n`, output the **index** of `nums`among all the permutations.
- Given `n` and an index `idx` (which is in range of `[0, n!)`), output the corresponding sequence `nums`.

Please note that each element in `nums` is distinct here.  We will consider the case that **elements are not unique** in the "Follow Up" chapter.

And this is what **Cantor Expansion** want to solve.



## Cantor Expansion

You can read [Baidu baike](https://baike.baidu.com/item/%E5%BA%B7%E6%89%98%E5%B1%95%E5%BC%80/7968428), not good article, not good code, but good examples.

- Given `n`, and a sequence `nums[0, ..., n - 1]`, and `1 <= nums[i] <= n`.
- Let $a_i$ denote the number of "Reverse-Order-Pairs" of `nums[i]`.
  - A "Reverse-Order-Pair" is a pair `<i, j>` that satisfies `i < j && nums[i] > nums[j]` .
  - This is similar to "[LCOF 51. 数组中的逆序对](https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/)".

Then there is a bijection ("双射" in Chinese) between indice and permutations.

That is to say, the index of `nums` is:
$$
\text{index} = a_0 \cdot (n-1)! + a_1 \cdot (n-2)! + \dots + a_{n-2}\cdot(1!) + a_{n-1} \cdot (0!)
$$
It seems quite simple and naive :-D.  Let us take a look why this formula work!



## Permutation to Index

**Description** - Given `n`, and a sequence `nums[0, ..., n - 1]`, and `1 <= nums[i] <= n`, output the **index** of `nums`.

Our algorithm:

- Init returned value `index = 0`.
- For `nums[i]`, we find the number of "Reverse-Order-Pairs" of it, which is denoted by `revCnt`.
  - A "Reverse-Order-Pair" is a pair `<i, j>` that satisfies `i < j && nums[i] > nums[j]` .
  - This is similar to "[LCOF 51. 数组中的逆序对](https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/)".
  - Let `index += f(n - i - 1) * revCnt`, where `f(x)` denote the value `x!` , and `n - i - 1` denote the remained length.

Let me explain this algorithm by an exmaple.

```text
input   : [4, 3, 1, 2]
expected: 22
revCnt  : [3, 2, 0, 0]
offset  : [18,4, 0, 0]
---------
When i = 0, nums[i] = 4, revCnt = 3
  - Before "4XXX", there should be permutations in patterns like "3XXX", "2XXX", "1XXX".
  - The remained length is `n - i - 1 = 3` (i.e. the length of "XXX").
  - The total number of permutations in those patterns is 3 * 3! = 18.
---------
When i = 1, nums[i] = 3, revCnt = 2
  - Before "43XX", there should be permutations in patterns like "41XX", "42XX".
  - The remained length is 2.
  - The total number of permutations in those patterns is 2 * 2! = 4.
---------
When i = 2, nums[i] = 1, revCnt = 0
  - Since there is no `nums[j]` less than `1`, hence there is no permutation before "431X"
---------
When i = 3, nums[i] = 2, revCnt = 0
  - Same as `i = 2`
```

The `revCnt` means that "there are `revCnt` numbers are smaller than me on my right side".

Here is my code, including tests.

```cpp
class PermIndex {
private:
    unordered_map<int, vector<int>> bench;
    unordered_map<int, vector<int>> benchmark(vector<int> vec) {
        unordered_map<int, vector<int>> res;
        sort(vec.begin(), vec.end());
        int idx = 0;
        do {
            res[idx++] = vec;
        } while (next_permutation(vec.begin(), vec.end()));
        return res;
    }

public:
    PermIndex(vector<int> &nums) { bench = benchmark(nums); }

    int permToIndex(vector<int> &nums) {
        int n = nums.size();
        // fact[k] = k!
        vector<int> fact(n, 1);
        for (int i = 2; i < n; ++i) fact[i] = fact[i - 1] * i;

        int index = 0;
        for (int i = 0; i < n; ++i) {
            int revCnt = 0;
            for (int j = i + 1; j < n; ++j)
                revCnt += (nums[j] < nums[i]);
            index += fact[n - i - 1] * revCnt;
        }
        assert(nums == bench[index]);
        return index;
    }
};

int main() {
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7};
    PermIndex permIndex(vec);
    do {
        cout << permIndex.permToIndex(vec) << endl;
    } while (next_permutation(vec.begin(), vec.end()));
}
```

Obviously, the time complexity is $O(n^2)$. 



## Index To Permutation

**Description** - Given `n` and an index `idx` (which is in range of `[0, n!)`), output the corresponding sequence `nums`.

The problem here is same as "[60. Permutation Sequence](https://leetcode.com/problems/permutation-sequence/)".

```cpp
class Solution {
public:
    string getPermutation(int n, int k) {
        string res;
        vector<int> fact(n + 1, 1);
        vector<char> nums(n, '0');
        for (int i = 1; i <= n; ++i) {
            fact[i] = fact[i - 1] * i;
            nums[i - 1] += i;
        }
        
        k -= 1;  // our index starts with 0
        for (int i = 0; i < n; ++i) {
            int cnt = k / fact[n - i - 1];
            res.push_back(nums[cnt]);
            nums.erase(nums.begin() + cnt);
            k -= cnt * fact[n - i - 1];  // or k %= fact[n - i - 1]
        }
        return res;
    }
};
```

This algorithm is actually an inverse-process of above "Permutation To Index".

- Remind that we let `index += fact[n - i - 1] * revCnt` above, where `index` is denoted by `k` here.
- Here, we let `cnt = k / fact[n - i - 1]`, where `cnt` means that, "there are `cnt` numbers smaller than me". Hence we put `nums[cnt]` into the result string, since `nums[0, ... cnt - 1]` is smaller than `nums[cnt]`. 
- Let `k = k % fact[n - i - 1]` or `k -= cnt * fact[n - i - 1]` .
- Continue the above steps until `k` become zero (it is inevitable since `fact[1] = fact[0] = 1`), or until `nums` is empty.

Same as above, let me explain this algorithm by an example.

```text
input    : n = 4, k = 22
expected : [4, 3, 1, 2]
nums     : [1, 2, 3, 4] (index starts with 0)
factorial: [1, 1, 2, 6, 24] 
--------
When i = 1, k = 22:
  - cnt = 22 / fact[3] = 3, among the `nums`, there are 3 numbers smaller than me on the right side
  - hence current number should be 4, and the result should be '4XXX'
  - k = 22 % 6 = 4
When i = 2, k = 4:
  - cnt = 4 / fact[2] = 2, among the `nums`, there are 2 numbers smaller than me on the right side
  - hence the result should be '43XX'
  - k = 4 % 2 = 0
When i = 3, k = 0:
  - cnt = 0, among the `nums`, there is no number smaller than me
  - hence the result should be '431X'
When i = 4, k = 0:
  - cnt = 0, the result is '4312'
```



## Follow Up

Given a certain permutation of n literals (e.g. "BCDA" is a permutation of literals "ABCD"). Find out its index of this permutation in the full permutation of these `n (n <= 1000)` literals when sorted in alphabetical order.

Please note that: 

- The letters in `str` are not unique, there maybe exist duplicate letters, such as `s = "AABBSDFS"`.
- The numbers of permutations is less than $n!$ .

Actually, the total number of permutations for the given `str` is:
$$
\frac{n!}{(p_1!) \cdot (p_2!) ... (p_{k}!)}
$$
where $n$ is the length of `str`, $k$ is the number of unique characters of `str`, and $p_i$ is the number of occurrences of `set(str)[i]`.

Since there are duplicate characters in the input `string`, the key point of this problem is how to remove the duplicate permutations.

Still, let me show you an example.

```text
input   : "A A B C B C C"
revCnt  : [0 0 0 1 0 0 0]
expected: 1
--------
Count occurrences of input: {{A:2}, {B:2}, {C:3}}
When i = 0, 1, 2:
  - The number of Reverse-Order-Pairs of `nums[i]` is zero, i.e. revCnt = 0
When i = 3, we are at the status of "AABC???"
  - revCnt = 1, that means, before "AABC???", there are permutations in a pattern "AABB???"
  - The remained length is 3.
  - The number of such permutation is (3!) / (3!) = 1
  _ index += 1
When i = 4, 5, 6:
  - revCnt = 0, do nothing
```

Let me make the case `i = 3` more clear.

- Obviously, there are 3 empty position in the remained length `"???"` in `"AABB???"`, hence we can have `3!` permutations.
- But there exists duplicate permutations, since the remained letters we can use is `{C : 3}`. See the formula at the begin of this section.

Here is the code :-P.

```cpp
class PermIndex {
private:
    unordered_map<int, string> bench;
    unordered_map<int, string> benchmark(string str) {
        unordered_map<int, string> res;
        sort(str.begin(), str.end());
        int idx = 0;
        do {
            res[idx++] = str;
        } while (next_permutation(str.begin(), str.end()));
        return res;
    }

public:
    PermIndex(string &str) { bench = benchmark(str); }

    /**
     * compute(cnt, len) aim to solve such a problem, using the chars in the
     * `cnt` (maybe have duplicate characters, but total numbers of chars is
     * `len`) to combine a permutation of length `len`, how many permutations we
     * can get?
     */
    int compute(unordered_map<char, int> &cnt, vector<int> &fact, int len) {
        int res = fact[len];
        for (auto [ch, val] : cnt)
            res /= fact[val];
        return res;
    }

    int permToIndex(const string &str) {
        int n = str.length();

        vector<int> fact(n, 1);
        for (int i = 2; i < n; ++i)
            fact[i] = fact[i - 1] * i;

        unordered_map<char, int> cnt;
        for (char x : str)
            cnt[x]++;

        int index = 0;
        for (int i = 0; i < n; ++i) {
            unordered_set<char> smaller;
            for (int j = i + 1; j < n; ++j)
                if (str[j] < str[i])
                    smaller.emplace(str[j]);

            for (char x : smaller) {
                cnt[x] -= 1;
                index += compute(cnt, fact, n - i - 1);
                cnt[x] += 1;
            }

            cnt[str[i]] -= 1;
        }
        assert(str == bench[index]);
        return index;
    }
};

int main() {
    // string str = "AABBSDABFS";
    string str = "BBSAASDABFS";
    PermIndex permIndex(str);
    int idx = 0;
    do {
        printf("%d : %s \n", idx++, str.c_str());
        permIndex.permToIndex(str);
    } while (next_permutation(str.begin(), str.end()));
}
```

And it's quite challenging to solve problem "Index To Permutation" when the input has duplicate characters.

But it's still the inverse-process of the algorithm above, we just need to pay attention to the details. 

To be done.



