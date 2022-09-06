## LCP 30. 魔塔游戏

Leetcode: [LCP 30. 魔塔游戏](https://leetcode.cn/problems/p0NxJO/)

小扣当前位于魔塔游戏第一层，共有 `N` 个房间，编号为 `0 ~ N-1`。每个房间的补血道具/怪物对于血量影响记于数组 `nums`，其中正数表示道具补血数值，即血量增加对应数值；负数表示怪物造成伤害值，即血量减少对应数值；0 表示房间对血量无影响。

小扣初始血量为 1，且无上限。假定小扣原计划按房间编号升序访问所有房间补血/打怪，为保证血量始终为正值，小扣需对房间访问顺序进行调整，每次仅能将一个怪物房间（负数的房间）调整至访问顺序末尾。请返回小扣最少需要调整几次，才能顺利访问所有房间。若调整顺序也无法访问完全部房间，请返回 -1。

示例 1：
```
输入：nums = [100,100,100,-250,-60,-140,-50,-50,100,150]
输出：1
解释：初始血量为 1。至少需要将 nums[3] 调整至访问顺序末尾以满足要求。
```
示例 2：
```
输入：nums = [-200,-300,400,0]
输出：-1
解释：调整访问顺序也无法完成全部房间的访问。
```
提示：

- `1 <= nums.length <= 10^5`
- `-10^5 <= nums[i] <= 10^5`

**贪心 + 优先队列**

首先，判断 `sum(nums) + 1 >= 1` ，否则不论怎么调整顺序，无法访问全部的房间。如果 `sum(nums) + 1 >= 1` 成立，那么必然能够通过调整顺序，访问全部的房间。

基本设定：

- 如果 `nums[i] >= 0` ，必访问之，因为可以回血。
- 如果 `nums[i] < 0`，我们不一定要现在访问它（血量够的话允许访问），可以选择把它放在最后。`nums[i]` 越小，那么它的位置就越靠后。

模拟这个过程：

- 从左到右遍历每一个 `x = nums[i]`，累计到血量 `blood` 中。
- 如果 `blood` 小于 0，那么说明前面有个房间 `nums[i]` 我们需要跳过它（并把它放在最后）。
- 那么应该如何选择跳过的房间呢？血量扣得越多，应该被优先选择，所以使用一个优先队列，去记录 `nums[i] < 0` 的房间。

```cpp
class Solution {
public:
    int magicTower(vector<int>& nums)
    {
        // Pay attention to '0LL', since sum up of nums may int32-overflow 
        int64_t sum = accumulate(begin(nums), end(nums), 0LL);
        if (sum + 1 <= 0)
            return -1;

        // Put the minimum negative number on the top
        priority_queue<int, vector<int>, greater<int>> que;
        int res = 0;
        int64_t blood = 1;
        for (int x: nums)
        {
            if (x < 0) que.emplace(x);

            blood += x;
            while (blood <= 0 && !que.empty())
            {
                blood += std::abs(que.top());
                que.pop();
                res++;
            }
        }
        return res;
    }
};
```

