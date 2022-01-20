## [leetcode] 周赛 223

🏆 比赛题目：https://leetcode-cn.com/contest/weekly-contest-223/.

## 解码异或后的数组

题目：[1720. 解码异或后的数组](https://leetcode-cn.com/problems/decode-xored-array/)。

还记得数列求和的「累加法」？

已知 `encoded[i] = arr[i] ^ arr[i + 1]` ，展开之：

```
e[0] = a[0] ^ a[1]
e[1] = a[1] ^ a[2]
e[2] = a[2] ^ a[3]
...
e[i-1] = a[i-1] ^ a[i] 
```

等号两边所有数字同时异或：

```
e[0] ^ ... ^ e[i-1] = a[0] ^ a[i]
==>
a[i] = a[0] ^ e[0] ^ ... ^ e[i-1]
```

代码：

```cpp
class Solution {
public:
    vector<int> decode(vector<int>& encoded, int first) {
        int n = encoded.size();
        vector<int> a(n+1, first);
        int x = 0;
        for (int i=1; i<=n; i++)
        {
            x ^= encoded[i-1];
            a[i] ^= x;
        }
        return a;
    }
};
```

## 交换链表中的节点

题目：[1721. 交换链表中的节点](https://leetcode-cn.com/problems/swapping-nodes-in-a-linked-list/)。

双指针。

```cpp
class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr) return head;
        auto p = head, q = head;
        int i=0;
        for (i=1; i<k && q != nullptr; i++) q = q->next;
        // 第 k 个节点
        auto t = q;
        q = q->next;
        if (q == nullptr && i<k) return head;
		// 倒数第 k 个节点
        while (q != nullptr) p = p->next, q = q->next;
        swap(t->val, p->val);
        return head;
    }
};
```

## 执行交换操作后的最小汉明距离 

题目：[1722. 执行交换操作后的最小汉明距离](https://leetcode-cn.com/problems/minimize-hamming-distance-after-swap-operations/)。

类题题目：[1202. 交换字符串中的元素](https://leetcode-cn.com/problems/smallest-string-with-swaps/) 。

对于 `swaps` 给出的序列对，可以构成一个图，允许交换的节点（节点的标识符是下标）组成一个联通分量。通过并查集来「分离」出联通分量，记录在 `map<int, vector>` 中，其 `key` 值为联通分量的根。

对于每个连通分量，从 `source` 和 `target` 中都能够得到一个对应的集合（具有重复元素的集合），记为 `s` 和 `t`。该连通分量所贡献的汉明重量就是 `s` 和 `t` 中不同的元素个数。实际上，这里求的是 `s` 和 `t` 的对称差集的大小（某些教材称这种运算为环和 $\bigoplus$）。

下面以输入  `source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]` 为例。

可以得到 2 个联通分量：

```
table[0] = [0, 1]
table[2] = [2, 3]
```

对于连通分量 `[0,1]`，所得集合 `s = {1,2}, t = {1,2}`，没有元素不同，因此贡献的汉明重量为 0 。

对于连通分量 `[2,3]`，所得集合 `s = {3,4}, t = {4,5}`，不同元素个数为 1，因此汉明重量为 1 。

由于输入可能存在重复元素，因此需要使用 `multiset` .

```cpp
class Solution {
public:
    vector<int> root;
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = source.size();
        root.resize(n, -1);
        for (auto &v: allowedSwaps) merge(v[0], v[1]);
        unordered_map<int, vector<int>> table;
        for (int i=0; i<n; i++) table[find(i)].push_back(i);
        
        int w = 0;
        for (auto &[k,v]: table)
        {
            unordered_multiset<int> s,t;
            for (int i: v) s.insert(source[i]), t.insert(target[i]);
            for (int x: s)
            {
                auto itor = t.find(x);
                if (itor == t.end()) w++;
                else t.erase(itor);
            }
        }
        return w;
    }
    int find(int x) { return root[x] == -1 ? x : root[x] = find(root[x]); }
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x != y) root[y] = x;
    }
};
```

## 完成所有工作的最短时间

题目：[1723. 完成所有工作的最短时间](https://leetcode-cn.com/problems/find-minimum-time-to-finish-all-jobs/)。

原本的想法是基于贪心实现，初始化一个大小为 `k` 的优先队列，每次选出当前工作时间最小的工人，分配一个工作，最后求出所有工人工作时间的最大值。但很显然，样例 2 就不满足了。

这是最大值极小化（最小值极大化）类型的题目，使用状态压缩的动态规划。

参考[题解](https://leetcode-cn.com/problems/find-minimum-time-to-finish-all-jobs/solution/zhuang-ya-dp-jing-dian-tao-lu-xin-shou-j-3w7r/)。

设 $n$ 为 `jobs` 的长度，那么 `jobs` 产生的子集个数为 $2^n$ , 我们使用 $[0, 2^n]$ 上的整数来标记每个子集。例如：

```
n = 3, jobs = [1,2,3]
000 => []
001 => [1]
010 => [2]
011 => [1,2]
100 => [3]
101 => [1,3]
110 => [2,3]
111 => [1,2,3]
```

令 `total[x]` 为子集 `x` 的总工作时间，设子集 `x` 中的任意一个元素为 `j` ，则 `x - (1 << j)` 表示去除元素 `j` 后的子集，因此有：

```cpp
total[x] = total[x - (1 << j)] + jobs[j]
```

注意：这里我们只需要任意的一个 `j` 即可，比如子集 `[1,2,3]` ，我们可以通过下面 3 种方法计算：

+ `total([1,2,3]) = total([1,2]) + jobs[3]`
+ `total([1,2,3]) = total([1,3]) + jobs[2]`
+ `total([1,2,3]) = total([2,3]) + jobs[1]`

然后，令 `dp[j][i]` 为前 `j` 个工人（包括第 `j` 个），完成任务集合 `i` 的最小工作时间。其中，$0 \le j \le k-1, 0 \le i \le 2^n-1$ . 工人标号从 `0` 到 `k-1` .

对于 `dp[j][i]` 而言，`j` 号工人必然完成了某一个子集，因此需要遍历 `i` 的每一个子集 `s` ，`max(total[s], dp[j-1][i-s])` 为工人 `j` 完成子集 `s` 时的最佳工作时间，然而我们需要的是一个全局最佳的工作时间，所以需要挑选一个最优的子集。

因此状态转移方程为：
$$
dp[j][i] = \min_{s \subseteq i}{\{ \max(total[s], dp[j-1][i-s]) \}}
$$
代码：

```cpp
class Solution
{
public:
    int minimumTimeRequired(vector<int> &jobs, int k)
    {

        int n = jobs.size();
        const int m = 1 << n;
        vector<int> total(m, 0);
        for (int i = 1; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if ((i & (1 << j)) != 0)
                {
                    total[i] = total[i - (1 << j)] + jobs[j];
                    break;
                }
            }
        }
        vector<vector<int>> dp(k, vector<int>(m, 0));
        for (int i = 0; i < m; i++) dp[0][i] = total[i];
        for (int j = 1; j < k; j++)
        {
            for (int i = 1; i < m; i++)
            {
                int val = 0x7fffffff;
                for (int s = i; s; s = (s - 1) & i)
                    val = min(val, max(total[s], dp[j - 1][i - s]));
                dp[j][i] = val;
            }
        }
        return dp[k-1][m-1];
    }
};

```

