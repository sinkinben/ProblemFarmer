## Meeting Rooms

- [252. Meeting Rooms](https://leetcode.com/problems/meeting-rooms)
- [253. Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii)
- [2402. Meeting Rooms III](https://leetcode.com/problems/meeting-rooms-iii/)



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



## Meeting Rooms III

You are given an integer `n`. There are `n` rooms numbered from `0` to `n - 1`.

You are given a 2D integer array `meetings` where `meetings[i] = [starti, endi]` means that a meeting will be held during the **half-closed** time interval `[starti, endi)`. All the values of `starti` are **unique**.

Meetings are allocated to rooms in the following manner:

1. Each meeting will take place in the unused room with the **lowest** number.
2. If there are no available rooms, the meeting will be delayed until a room becomes free. The delayed meeting should have the **same** duration as the original meeting.
3. When a room becomes unused, meetings that have an earlier original **start** time should be given the room.

Return *the **number** of the room that held the most meetings.* If there are multiple rooms, return *the room with the **lowest** number.*

A **half-closed interval** `[a, b)` is the interval between `a` and `b` **including** `a` and **not including** `b`.



**Example 1:**

```
Input: n = 2, meetings = [[0,10],[1,5],[2,7],[3,4]]
Output: 0
Explanation:
- At time 0, both rooms are not being used. The first meeting starts in room 0.
- At time 1, only room 1 is not being used. The second meeting starts in room 1.
- At time 2, both rooms are being used. The third meeting is delayed.
- At time 3, both rooms are being used. The fourth meeting is delayed.
- At time 5, the meeting in room 1 finishes. The third meeting starts in room 1 for the time period [5,10).
- At time 10, the meetings in both rooms finish. The fourth meeting starts in room 0 for the time period [10,11).
Both rooms 0 and 1 held 2 meetings, so we return 0. 
```

**Example 2:**

```
Input: n = 3, meetings = [[1,20],[2,10],[3,5],[4,9],[6,8]]
Output: 1
Explanation:
- At time 1, all three rooms are not being used. The first meeting starts in room 0.
- At time 2, rooms 1 and 2 are not being used. The second meeting starts in room 1.
- At time 3, only room 2 is not being used. The third meeting starts in room 2.
- At time 4, all three rooms are being used. The fourth meeting is delayed.
- At time 5, the meeting in room 2 finishes. The fourth meeting starts in room 2 for the time period [5,10).
- At time 6, all three rooms are being used. The fifth meeting is delayed.
- At time 10, the meetings in rooms 1 and 2 finish. The fifth meeting starts in room 1 for the time period [10,12).
Room 0 held 1 meeting while rooms 1 and 2 each held 2 meetings, so we return 1. 
```

 

**Constraints:**

- `1 <= n <= 100`
- `1 <= meetings.length <= 1e5`
- `meetings[i].length == 2`
- `0 <= starti < endi <= 5 * 1e5`
- All the values of `starti` are **unique**.

<br/>

**Solution**

- Min heap `rooms` to track the available rooms.
- Min heap `pq` to track those on-holding meetings.
- For each meeting `m[i] = {start, end}`, we should pop some rooms from `pq` (if there exists some meetings that are finished). Otherwise, we must delay current `m[i]`.

```cpp
using vec = vector<int>;
struct meeting
{
    int64_t start, end, room;
    meeting(int64_t s, int64_t e, int r) : start(s), end(e), room(r) {}
    bool operator<(const meeting &m) const 
    {
        return end > m.end || (end == m.end && room > m.room);
    }
};
class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        std::sort(begin(meetings), end(meetings));
        
        priority_queue<int, vector<int>, greater<int>> rooms;
        for (int i = 0; i < n; ++i)
            rooms.push(i);
        
        priority_queue<meeting> pq;  // record meetings that are holding
        vector<int> freq(n, 0);
        for (auto &m : meetings)
        {
            int start = m[0], end = m[1];
            while (!pq.empty() && pq.top().end <= start)
            {
                auto mt = pq.top();
                pq.pop();
                rooms.push(mt.room);
            }
            if (!rooms.empty())
            {
                int r = rooms.top();
                rooms.pop();
                freq[r]++;
                pq.emplace(start, end, r);
            }
            else
            {
                // must to make a delay
                assert(!pq.empty());
                auto mt = pq.top();
                pq.pop();
                // pay attention to overflow
                pq.emplace(mt.end, mt.end + end - start, mt.room);
                freq[mt.room]++;
            }
        }
        
        return std::distance(begin(freq), std::max_element(begin(freq), end(freq)));
    }
};
```

