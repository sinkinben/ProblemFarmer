## Interval Problems

Leetcode:

- [56. Merge Intervals](https://leetcode.com/problems/merge-intervals/)
- [435. Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/)
- [452. Minimum Number of Arrows to Burst Balloons](https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/)
- [252. Meeting Rooms](https://leetcode.com/problems/meeting-rooms)
- [253. Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii)



## [Merge Intervals](https://leetcode.com/problems/merge-intervals/)

Given an array of `intervals` where `intervals[i] = [starti, endi]`, merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.

```text
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
```

<br/>

**Solution**

- Sort the `intervals` vector.
- Greedily merge the intervals forward.

```cpp
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) 
    {
        vector<vector<int>> res;
        sort(intervals.begin(), intervals.end());
        int n = intervals.size(), i = 0;
        while (i < n)
        {
            auto &v = intervals[i];
            int j = i + 1;
            while (j < n && canMerge(v, intervals[j])) v = merge(v, intervals[j++]);
            res.emplace_back(v);
            i = j;
        }
        return res;
    }
    
    bool canMerge(vector<int> &v1, vector<int> &v2) { return v2[0] <= v1[1]; }
    
    vector<int> &merge(vector<int> &v1, vector<int> &v2)
    {
        v1[1] = max(v1[1], v2[1]);
        return v1;
    }
};
```





## [Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/)

Given an array of intervals `intervals` where `intervals[i] = [starti, endi]`, return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

```text
Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.
```

<br/>

**Solution**

The problem here is to find the max number of non-overlapping intervals. On the other hand, we should find which intervals should be removed.

- Sort the `intervals` according to their end points.
- Greedily iterate `intervals` from left to right, mark the right-most bounder.
- If `intervals[i].left < right`, then `intervals[i]` is conflict with those intervals we have selected. We should remove it.

For example,

```
         right bounder
           |
           V
  +--------|
     +-----|
+----------|
        +-------|
              +----|
```

The first **four** intervals are conflicting (they are overlapping), we should remove three of them. 

For the last one, we should track the new right-bounder.

```cpp
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;
        
        sort(begin(intervals), end(intervals), [](auto &v1, auto &v2) {
           return v1[1] < v2[1]; 
        });
        
        int n = intervals.size(), remove = 0;
        int right = intervals[0][1];
        for (int i = 1; i < n; ++i)
        {
            if (intervals[i][0] < right)
                remove++;
            else
                right = intervals[i][1];
        }
        return remove;
    }
};
```

Of course, we can sort `intervals` according to their **left bounders**.

```cpp
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;
        
        sort(begin(intervals), end(intervals));
        
        int n = intervals.size(), remove = 0;
        int left = intervals[n - 1][0];
        for (int i = n - 2; i >= 0; --i)
        {
            if (intervals[i][1] > left)
                remove++;
            else
                left = intervals[i][0];
        }
        return remove;
    }
};
```



## [Minimum Number of Arrows to Burst Balloons](https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/)

There are some spherical balloons taped onto a flat wall that represents the XY-plane. The balloons are represented as a 2D integer array `points` where `points[i] = [start, end]` denotes a balloon whose **horizontal diameter** stretches between `start` and `end`. You do not know the exact y-coordinates of the balloons.

Arrows can be shot up **directly vertically** (in the positive y-direction) from different points along the x-axis. A balloon with `start` and `end` is **burst** by an arrow shot at `x` if `xstart <= x <= xend`. There is **no limit** to the number of arrows that can be shot. A shot arrow keeps traveling up infinitely, bursting any balloons in its path.

Given the array `points`, return *the **minimum** number of arrows that must be shot to burst all balloons*.

<br/>

**Solution**

It's similar to [435. Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/).

- Obviously, the overlapping intervals can be shoted by **ONE** arrow.
- The max number of non-overlapping intervals, is equal to "the min number of arrows to shot all balloons".

```cpp
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        auto &intervals = points;
        if (intervals.empty()) return 0;
        sort(begin(intervals), end(intervals), [](auto &i1, auto &i2) { return i1[1] < i2[1]; });
        int n = intervals.size(), remove = 0;
        int right = intervals[0][1];
        for (int i = 1; i < n; ++i)
        {
            /* Pay attention here: [1, 2] and [2, 3] are overlapping,
             * which is different from 435-Non-overlapping-Intervals.
             */
            if (intervals[i][0] <= right) remove++;
            else right = intervals[i][1];
        }
        /* We should remove `k` intervals to get max number of non-overlapping intervals.
         * Hence the number of non-overlaopping intervals is `n - k`.
         */
        return n - remove;
    }
};
```



## [Meeting Rooms](https://leetcode.com/problems/meeting-rooms)

Given an array of meeting time `intervals` where `intervals[i] = [start, end]`, determine if a person could attend all meetings.

```text
Input: intervals = [[0,30],[5,10],[15,20]]
Output: false
```

<br/>

**Solution**

An instuitive solution is: sort by the left-bounders, and the adjacent intervals can not be overlapping.

```cpp
class Solution 
{
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) 
    {
        sort(intervals.begin(), intervals.end());
        int n = intervals.size();
        for (int i = 1; i < n; ++i)
            if (intervals[i - 1][1] > intervals[i][0]) return false;
        return true;
    }
};
```

Another idea: he max number of non-overlapping intervals should be `n`.

```cpp
class Solution {
public:
    int canAttendMeetings(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 1;
        
        sort(begin(intervals), end(intervals), [](auto &v1, auto &v2) {
           return v1[1] < v2[1]; 
        });
        
        int n = intervals.size(), remove = 0;
        int right = intervals[0][1];
        for (int i = 1; i < n; ++i)
        {
            if (intervals[i][0] < right) remove++;
            else right = intervals[i][1];
        }
        return remove == 0;
    }
};
```



## [Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii)

Given an array of meeting time intervals intervals where `intervals[i] = [starti, endi]`, return the minimum number of conference rooms required.

Constraints: `1 <= intervals.length <= 10^4, 0 <= starti < endi <= 10^6`

**Example 1**

```
Input: intervals = [[0,30],[5,10],[15,20]]
Output: 2
```

**Example 2**

```
Input: intervals = [[7,10],[2,4]]
Output: 1
```

<br/>

**Solution**

- Suppose we have a timeline, on each time point of this timeline, someone can apply for a room (+1), or return a room (-1).
- For each element `[start, end]` in `intervals` array, at the `start` time, we should apply for a room, and return it at `end` time.
- If there are applying requests and returning requests at the same time, we should **accept the returning requests firstly.**

```cpp
class Solution 
{
public:
    int minMeetingRooms(vector<vector<int>>& intervals) 
    {
        if (intervals.size() == 0) return 0;
        map<int, int> timeline; // time -> number of rooms we need
        for (auto &interval : intervals)
        {
            timeline[interval[0]] += 1;   // get a room
            timeline[interval[1]] -= 1;   // return a room
        }
        
        int res = 0, sum = 0;
        for (auto [time, val] : timeline)
            sum += val, res = max(res, sum);
        return res;
    }
};
```

