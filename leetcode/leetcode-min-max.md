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
  - Divide `nums` into `k` parts, minimize the max-sum among `k` parts.
- [410. Split Array Largest Sum](https://leetcode-cn.com/problems/split-array-largest-sum/) - Min-max
  - Divide `nums` into `k` subarrays (need to be consecutive), minimize the max-sum among `k` subarrays.
- [1011. Capacity To Ship Packages Within D Days](https://leetcode-cn.com/problems/capacity-to-ship-packages-within-d-days/) - Same as 410.

**Group - 2**

- [1986. Minimum Number of Work Sessions to Finish the Tasks](https://leetcode-cn.com/problems/minimum-number-of-work-sessions-to-finish-the-tasks/)
- Put items into `n` boxes, the size of each box is `sessionTime`, minimize such number `n`.
- [875. Koko Eating Bananas](https://leetcode-cn.com/problems/koko-eating-bananas/)
  - Put items into `h` boxes, each item should be: `item <= box.size`, minimize the size of the box `size`.

**Others**


- [1482. Minimum Number of Days to Make m Bouquets](https://leetcode-cn.com/problems/minimum-number-of-days-to-make-m-bouquets/)
- Use min days to get max number of bouquets.
- [774. Minimize Max Distance to Gas Station](https://leetcode-cn.com/problems/minimize-max-distance-to-gas-station/)
