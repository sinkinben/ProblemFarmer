## Min-max Problems

> Refer to: [Minimax and Maximin Optimization](http://apmonitor.com/me575/index.php/Main/MiniMax)
>
> A minimax problem seeks to minimize the maximum value of a number of decision variables. It is sometimes applied to minimize the possible loss for a worst case (maximum loss) scenario.
>
> A maximin problem maximizes the minimum value. It is used to maximize the minimum objective (such as profit or revenue) for all potential scenarios.

Usually, we have two strategies to solve Min-max or max-min problems.

- Binary Search
- Dynamic Programming



**Group - 1**

- [1723. Find Minimum Time to Finish All Jobs](https://leetcode-cn.com/problems/find-minimum-time-to-finish-all-jobs/) - Min-max
  - Divide `nums` into `k` parts (non-empty subset), minimize the max-sum among `k` parts.
- [410. Split Array Largest Sum](https://leetcode-cn.com/problems/split-array-largest-sum/) - Min-max
  - Divide `nums` into `k` subarrays (consecutive), minimize the max-sum among `k` subarrays.
  - [1011. Capacity To Ship Packages Within D Days](https://leetcode-cn.com/problems/capacity-to-ship-packages-within-d-days/) - Same as 410.
- [1231. Divide Chocolate](https://leetcode-cn.com/problems/divide-chocolate/) - Max-min
  - Divide `nums` into `k` subarrays (consecutive), maximize the min-sum among `k` subarrays.
  - A dual problem of 410.

- [LCP 12. 小张刷题计划](https://leetcode-cn.com/problems/xiao-zhang-shua-ti-ji-hua/) - Min-max
  - Similar to 410.
  - Divide `nums` into `k` subarrays (consecutive), minimize the "max value of `SUM(sub) - MAX(sub)` among all subarrays".


**Group - 2**

- [1986. Minimum Number of Work Sessions to Finish the Tasks](https://leetcode-cn.com/problems/minimum-number-of-work-sessions-to-finish-the-tasks/)

  - Put items into `n` boxes, the size of each box is `sessionTime`, minimize such number `n`.
  - 每个盒子的大小固定为 `size` ，每个物品有固定的体积，一个盒子可以放入多个物品（如果放得下）。目标：最小化盒子的数量。

- [2064. Minimized Maximum of Products Distributed to Any Store](https://leetcode-cn.com/problems/minimized-maximum-of-products-distributed-to-any-store/)

  - 给定若干种物品，每个物品有一定数量，分配到 `k` 个盒子中，每个盒子只能放一种物品（数量可任意），目标：最小化「所有盒子中物品数量的最大值」。
  - [875. Koko Eating Bananas](https://leetcode-cn.com/problems/koko-eating-bananas/) - Same as 2064.

- [2594. 修车的最少时间](https://leetcode.cn/problems/minimum-time-to-repair-cars/)
  
  - 与上面类似，有 `n` 个汽车需要维修，需要分配到 `k` 个工人手上，工人所耗费工时的计算方式为 `ranks[i] * t * t`（`t` 表示分配到工人 `i` 的汽车数目）。目标：最小化「所有工人中的最大工时」。


**Others**


- [1482. Minimum Number of Days to Make m Bouquets](https://leetcode-cn.com/problems/minimum-number-of-days-to-make-m-bouquets/)

  - Use min days to get max number of bouquets.
- [774. Minimize Max Distance to Gas Station](https://leetcode-cn.com/problems/minimize-max-distance-to-gas-station/)
- [1631. Path With Minimum Effort](https://leetcode.com/problems/path-with-minimum-effort/)

  - Solution: https://www.cnblogs.com/sinkinben/p/16204077.html
