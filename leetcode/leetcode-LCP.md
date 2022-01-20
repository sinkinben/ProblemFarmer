## [leetcode] LCP 比赛

比赛题目：https://leetcode-cn.com/circle/discuss/MwNNcS/

## 黑白方格画

题目链接：[LCP 22. 黑白方格画](https://leetcode-cn.com/problems/ccw6C7/)。

**解题思路**

由于 $1 \le n \le 6$，所以可以考虑状态穷举。题目要求的是求出 `k` 个黑色格子的涂色方案个数，使用一个 `map<int, int>` 记录，例如 `map[1] = k` 表示黑色方格数目为 1 的涂色方案个数为 k 。

为了节省内存，我们使用一个 `int` 来表示每一行/列的着色状态，例如 `001100` 表示第 0, 1, 4, 5 行不涂色，第 2 行和第 3 行涂色。

现在需要穷举每一行和每一列的状态，`bist(n)` 表示 `n` 中 1 比特的数目：

```
for i=0 to 1<<n:
    for j=0 to 1<<n:
        x=bits(i), y=bits(j)
        map[(x+y)*n-x*y]++
return map[k]
```

**代码实现**

注意 `k == n * n` 的特殊情况。例如 `k=4, n=2` ，显然只有全部涂满这一种方案，但是 `(i,j)` 分别取 `(0,3)/(3,0)/(1,3)/(3,1)` 时，显然是重复着色的不合理情况（但循环中依然重复计数），因此需要特殊考虑。

```cpp
class Solution
{
public:
		int paintingPlan(int n, int k)
    {
        if (k == n*n)
            return 1;
        int limit = 1 << n;
        int x, y;
        unordered_map<int, int> m;
        for (int i = 0; i < limit; i++)
        {
            for (int j = 0; j < limit;j++)
            {
                x = popcount(i), y = popcount(j);
                if ((x + y) * n - x * y == n*n)
                    cout << i << ' ' << j << endl;
                m[(x + y) * n - x * y]++;
            }
        }
        return m[k];
    }

    int popcount(int x)
    {
        int k = 0;
        while (x!=0)
            x = x & (x - 1), k++;
        return k;
    }
};
```

## 魔术排列

题目链接：[LCP 23. 魔术排列](https://leetcode-cn.com/problems/er94lq/)。

**解题思路**

参考题解：https://leetcode-cn.com/problems/er94lq/solution/ji-suan-kzhi-bian-li-mo-ni-by-mazw-2/

以 `target = {2,4,3,1,5}` 为例，初始牌组为 `cards = {1,2,3,4,5}` ，洗牌一次后为：

```
target = [2 4 3 1 5]
cards1 = [2 4 1 3 5]
```

显然第一次洗牌的**最大**匹配长度 `firstMatch = 2` ，现在需要证明这个 `firstMatch` 其实就是题目所求的 `k` ，证明过程在[这里](https://leetcode-cn.com/problems/er94lq/solution/mo-ni-xi-pai-guo-cheng-xiang-xi-fen-xi-li-jie-kde-/)。个人理解是通过反证法去证明：

1. 假设 `k > firstMatch` ，那么在第一次取走牌的时候，取走 k 个，`[0, ..., firstMatch]` 可以匹配，但是在 `firstMatch + 1` 这个位置不能匹配，否则与 `firstMatch` 是第一次洗牌的最大匹配长度矛盾。
2. 假设 `k < firstMatch` ，那么第一次洗牌，取走 k 个；在第二次洗牌的时候，`cards[k+1, ..., firstMatch]` 被打乱和拆分到不同位置（并且后续无论怎么洗牌也无法让它们连续在一起，但是这些数字连续时才与 `target` 匹配），因此该情况不成立。

那么直接敲代码吧~

```cpp
class Solution
{
public:
    int firstMatch = -1;
    bool isMagic(vector<int> &target)
    {
        int n = target.size();
        vector<int> cards(n, 0);
        for (int i = 0; i < n; i++)
            cards[i] = i + 1;
        return shuffle(cards, target, 0);
    }

    bool shuffle(vector<int> &cards, const vector<int> &target, const int idx)
    {
        if (idx == (int)cards.size())
            return true;
        vector<int> tmp(cards);
        int size = tmp.size();
        int i = idx, j = idx + 1;
        for (; j < size; j += 2, i++)
            cards[i] = tmp[j];
        j = idx;
        for (; j < size; i++, j += 2)
            cards[i] = tmp[j];
        i = idx;
        while (i < size && target[i] == cards[i])
            i++;
        if (i == size)
            return true;

        int match = i - idx;
        if (firstMatch == -1)
            firstMatch = match;
        if (match == 0 || match < firstMatch)
            return false;

        return shuffle(cards, target, i);
    }
};
```

好像其他题目有点难0-0，所以就算了，该去吃饭了。

⏰ 2020/9/23 17:02