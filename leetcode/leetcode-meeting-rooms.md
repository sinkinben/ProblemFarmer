## Meeting Rooms

- [252. Meeting Rooms](https://leetcode.com/problems/meeting-rooms)
- [253. Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii)



## Meeting Rooms

**Description**

Given an array of meeting time intervals where `intervals[i] = [starti, endi]`, determine if a person could attend all meetings.

Constraints: `0 <= intervals.length <= 10^4, intervals[i].length == 2, 0 <= starti < endi <= 10^6`

**Example 1**

```text
Input: intervals = [[0,30],[5,10],[15,20]]
Output: false
```

**Example 2**

```text
Input: intervals = [[7,10],[2,4]]
Output: true
```

<br/>

**Solution**

Just sort the `intervals`.

```cpp
class Solution 
{
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) 
    {
        sort(intervals.begin(), intervals.end());
        int n = intervals.size();
        for (int i = 1; i < n; ++i)
        {
            if (intervals[i - 1][1] > intervals[i][0]) return false;
        }
        return true;
    }
};
```





## Meeting Rooms II

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

We reduce this problem into [1094. Car Pooling](https://leetcode.com/problems/car-pooling/).

- Suppose we have a timeline, on each time point of this timeline, someone can apply for a room, or return a room.
- For each element `[start, end]` in `intervals` array, at the `start` time, we should apply for a room, and return it at `end` time.
- If there are applying requests and returning requests at the same time, we should **accept the returning requests firstly.**

```cpp
class Solution 
{
public:
    int minMeetingRooms(vector<vector<int>>& intervals) 
    {
        if (intervals.size() == 0) return 0;
        vector<pair<int, int>> timeline;
        for (auto &interval : intervals)
        {
            timeline.emplace_back(interval[0], 1);  // get a room
            timeline.emplace_back(interval[1], -1); // return a room
        }
        
        sort(timeline.begin(), timeline.end(), [](auto &p1, auto &p2) {
           return (p1.first < p2.first) || (p1.first == p2.first && p1.second < p2.second); 
        });
        int res = 0, sum = 0;
        for (auto [time, val] : timeline)
            sum += val, res = max(res, sum);
        return res;
    }
};
```

We can also store `timeline` in a `map`.

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

For both of these solutions, time complexity is $O(n\log{n})$ .

