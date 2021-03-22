## [leetcode] 动态规划总结

来源于：https://leetcode.com/discuss/general-discussion/458695/Dynamic-Programming-Patterns

Leetcode 上的动态规划题目，可以分为以下几类：

+ Minimum/Maximum Cost to Reach A Target
+ Distinct Ways
+ Merging Intervals
+ DP on strings
+ Decision Making

本文算是翻译一下吧 🙂 ，持续更新。

## Min/Max Cost to Reach A Target

题目描述

> Given a target find minimum (maximum) cost / path / sum to reach the target.

解题思路

> Choose minimum (maximum) path among all possible paths before the current state, then add value for the current state.

转移方程

```cpp
routes[i] = min(routes[i-1], routes[i-2], ... , routes[i-k]) + cost[i]
```

关键点：找出当前状态所依赖的历史状态，取最大值/最小值。

习题集：

+ [746. 使用最小花费爬楼梯](https://leetcode-cn.com/problems/min-cost-climbing-stairs/)
+ [221. 最大正方形](https://leetcode-cn.com/problems/maximal-square/)
+ [322. 零钱兑换](https://leetcode-cn.com/problems/coin-change/)
+ [983. 最低票价](https://leetcode-cn.com/problems/minimum-cost-for-tickets/)
+ [650. 只有两个键的键盘](https://leetcode-cn.com/problems/2-keys-keyboard/)
+ [279. 完全平方数](https://leetcode-cn.com/problems/perfect-squares/)
+ [474. 一和零](https://leetcode-cn.com/problems/ones-and-zeroes/)
+ [64. 最小路径和](https://leetcode-cn.com/problems/minimum-path-sum/)
+ [120. 三角形最小路径和](https://leetcode-cn.com/problems/triangle/)
+ [931. 下降路径最小和](https://leetcode-cn.com/problems/minimum-falling-path-sum/)
+ [1046. 最后一块石头的重量](https://leetcode-cn.com/problems/last-stone-weight/)
+ [1049. 最后一块石头的重量 II](https://leetcode-cn.com/problems/last-stone-weight-ii/)
+ [1240. 铺瓷砖](https://leetcode-cn.com/problems/tiling-a-rectangle-with-the-fewest-squares/)
+ [174. 地下城游戏](https://leetcode-cn.com/problems/dungeon-game/)
+ [871. 最低加油次数](https://leetcode-cn.com/problems/minimum-number-of-refueling-stops/)

习题集解答：https://www.cnblogs.com/sinkinben/p/13603240.html

## Distinct Ways

题目描述

> Given a target, find a number of distinct ways to reach the target.

解题思路

> Sum all possible ways to reach the current state.