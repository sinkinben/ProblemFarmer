## Meeting Room II

Leetcode: [253. Meeting Rooms II](https://leetcode-cn.com/problems/meeting-rooms-ii/)

Given an array of meeting time intervals intervals where `intervals[i] = [starti, endi]`, return the minimum number of conference rooms required.

**Example**

```text
Input: intervals = [[0,30],[5,10],[15,20]]
Output: 2
```

**Solution**

```cpp
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        map<int, int> timeline;  // time -> number of rooms we need
        for (auto &v : intervals)
        {
            timeline[v[0]] += 1;
            timeline[v[1]] -= 1;
        }
        int rooms = 0, res = 0;
        for (auto [time, val] : timeline)
        {
            rooms += val;
            res = max(res, rooms);
        }
        return res;
    }
};
```



