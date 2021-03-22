## [leetcode] 周赛 209

🏆 比赛题目：https://leetcode-cn.com/contest/weekly-contest-209/

## 特殊数组的特征值

题目：[5531. 特殊数组的特征值](https://leetcode-cn.com/problems/special-array-with-x-elements-greater-than-or-equal-x/)。

注意到 `0 <= nums[i] <= 1000`，因此暴力枚举每个可能的 `x`。 

```cpp
class Solution {
public:
    int specialArray(vector<int>& nums) {
        int n = nums.size();
        for (int x=0;x<=1000;x++)
        {
            int k = count_if(nums.begin(), nums.end(),[x](const int e){return e>=x;});
            if (k == x) return x;
        }
        return -1;
    }
};
```



## 奇偶树

🌲 题目：[5532. 奇偶树](https://leetcode-cn.com/problems/even-odd-tree/)。

**解题思路**

按题目要求，层次遍历对每一层的序列进行判断即可。

**代码实现**

```cpp
class Solution {
public:
    bool isEvenOddTree(TreeNode* root) {
        if (root->val % 2 == 0)
            return false;
        auto p = root;
        queue<TreeNode*> q;
        q.push(p);
        int level = 0;
        while (!q.empty())
        {
            level++;
            vector<TreeNode*> next;
            while (!q.empty())
            {
                p = q.front(), q.pop();
                if (p->left)  next.push_back(p->left);
                if (p->right) next.push_back(p->right);
            }
            if (next.size() == 0)
                break;
            // check
            if (level % 2)
            {
                int n = next.size();
                for (int i=0;i<n-1;i++)
                {
                    if ((next[i]->val % 2 == 1) || (next[i+1]->val >= next[i]->val))
                        return false;
                }
                if (next[n-1]->val % 2 == 1)
                    return false;
            }
            else
            {
                int n = next.size();
                for (int i=0;i<n-1;i++)
                {
                    if ((next[i]->val % 2 == 0) || (next[i+1]->val <= next[i]->val))
                        return false;
                }
                if (next[n-1]->val % 2 == 0)
                    return false;
            }
            for (auto x: next)
            {
                // cout << x->val <<' ';
                q.push(x);
            }
            // cout<<endl;
            
        }
        return true;
    }
};
```

## 整数变为 0 的最少操作次数

题目：[5533. 使整数变为 0 的最少操作次数](https://leetcode-cn.com/problems/minimum-one-bit-operations-to-make-integers-zero/)。

+ **原本思路（❗️这是错误思路）**

不难发现 2 种操作必须是交替执行的（否则会陷入死循环），因此使用 DFS 暴力模拟。

但测试了几个测试用例，发现对于每一个具体的 `n` , 第一次操作应当是固定的（要么是 0 要么是 1），如果第一次操作不对，DFS 会陷入死循环。

因此这个解法是无效的。

```cpp
class Solution {
public:
    int ans = 0x3f3f3f3f;
    int minimumOneBitOperations(int n) {
        dfs(n, 0, 0);
        dfs(n, 0, 1);
        return ans;
    }
    void dfs(uint32_t n, int cnt, int op)
    {
        if (n == 0)
        {
            ans = min(ans, cnt);
            return;
        }
        if (op == 0)
            dfs(flip(n, 0), cnt+1, 1);
        else if (op == 1)
        {
            int i = 0;
            while (i < 32 && getbit(n, i) == 0)
                i++;
            dfs(flip(n, i+1), cnt+1, 0);
        }
    }

    inline uint32_t flip(uint32_t n, int i) { return n ^ (1 << i); }

    inline uint32_t getbit(uint32_t n, int i) { return ((n >> i) & 1); }
};
```

+ **讨论区解法**

规律：**格雷码转二进制码**，即：`n` 是第 x 项格雷码，求 `x` 的值。

```cpp
class Solution {
public:
    int minimumOneBitOperations(int n) {
        int ans = 0;
        while (n)
            ans ^= n, n = (n>>1);
        return ans;
    }
};
```

⚠️ 二进制码转格雷码：[89. 格雷编码](https://leetcode-cn.com/problems/gray-code/)。

```cpp
class Solution {
public:
    vector<int> grayCode(int n) {
        int len = (1 << n);
        vector<int> res;
        for (int i=0; i<len; i++)
            res.push_back(i ^ (i >> 1));
        return res;
    }
};
```

关于格雷码更详细的介绍：https://www.cnblogs.com/sinkinben/p/13768468.html .

还有一道题考三角函数，人晕了🤒️，果然长大了脑子都不好使，Let it go .