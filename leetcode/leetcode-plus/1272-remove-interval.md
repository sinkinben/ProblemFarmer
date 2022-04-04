## Remove Interval

Given a sorted list of disjoint `intervals`, each interval `intervals[i] = [a, b]` represents the set of real numbers `x` such that `a <= x < b`, i.e. `[a, b)`

We remove the intersections between any interval in `intervals` and the interval `toBeRemoved`.

Return a sorted list of `intervals` after all such removals.

<img src="https://assets.leetcode.com/uploads/2020/12/24/removeintervalex1.png" style="background:white;"/>

**Solution**

For each `i = intervals[i]`, perform a classified discussion.

- `i` should be removed, interval `i` is in the interval `remove`. i.e. `l < i[0] && i[1] < r`.
- `i` should be kept, i.e. `i[1] < l || r < i[0]`.
- `i` maybe overlapping with `remove` on its two sides. They may happend at the same time.

```cpp
class Solution {
public:
    vector<vector<int>> removeInterval(vector<vector<int>>& intervals, vector<int>& remove) {
        vector<vector<int>> res;
        int l = remove[0], r = remove[1];
        for (auto &i : intervals)
        {
            if (l <= i[0] && i[1] <= y)
                continue;
            if (i[1] < l || r < i[0])
                res.emplace_back(i);
            if (i[0] < l && l < i[1])
                res.emplace_back(vector{i[0], l});
            if (i[0] < r && r < i[1])
                res.emplace_back(vector{r, i[1]});
        }
        return res;
    }
};
```

