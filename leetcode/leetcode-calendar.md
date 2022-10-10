## [Leetcode] Calendar

- [729. My Calendar I](https://leetcode.com/problems/my-calendar-i/description/)
- [731. My Calendar II](https://leetcode.com/problems/my-calendar-ii/)
- [732. My Calendar III](https://leetcode.com/problems/my-calendar-iii/)



## 729. My Calendar I

题意：往集合添加区间 `[start, end)`，问是否可以添加成功（要求该区间与集合中的区间不相交）。

```cpp
class MyCalendar {
public:
    using pair_t = pair<int, int>;
    set<pair_t> st = {{0, 0}, {INT_MAX, INT_MAX}};

    MyCalendar() {}
    
    bool book(int start, int end)
    {
        auto it = st.lower_bound(pair_t{end, 0});
        // (it - 1)->first < end <= it->first
        if (start >= (--it)->second)
        {
            st.emplace(start, end);
            return true;
        }
        return false;
    }
};
```



## 731. My Calendar II

题意：往集合添加区间 `[start, end)`，问是否可以添加成功（不允许 3 个区间重叠）。

- `overlaps` 记录已经重叠的部分，`calendar` 记录添加过的区间。
- 如果待添加的 `p` 与 `overlaps` 中的某一元素有交集，那么说明出现了 3 个区间重叠。

```cpp
class MyCalendarTwo {
public:
    using pair_t = pair<int, int>;
    vector<pair_t> overlaps, calendar;
    MyCalendarTwo() { }
    
    bool isOverlap(pair_t p1, pair_t p2)
    {
        auto [s1, e1] = p1;
        auto [s2, e2] = p2;
        return !(e1 <= s2 || e2 <= s1);
    }
    
    bool book(int start, int end)
    {
        pair_t p = {start, end};
        for (auto e: overlaps)
            if (isOverlap(e, p)) return false;
        
        for (auto e: calendar)
            if (isOverlap(e, p))
                overlaps.emplace_back(max(p.first, e.first), min(p.second, e.second));
        calendar.emplace_back(p);
        return true;
    }
};
```



## [732. My Calendar III](https://leetcode.com/problems/my-calendar-iii/)

题意：往集合添加区间 `[start, end)`，返回集合中区间重叠的最大次数。

与「会议室」类似：时间点 `start` 需要申请一个会议室，因此 +1，时间点 `end` 归还一个会议室，因此 -1 ，记录所需会议室的最大数量。

**哈希表**

```cpp
class MyCalendarThree {
public:
    map<int, int> timeline;
    MyCalendarThree() {}
    
    int book(int start, int end) {
        timeline[start] += 1;
        timeline[end] -= 1;
        int res = 1, cnt = 0;
        for (auto [_, val]: timeline)
        {
            cnt += val;
            res = max(cnt ,res);
        }
        return res;
    }
};
```