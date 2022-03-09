## Remove Duplicates

Problems:

- [83. Remove Duplicates from Sorted List](https://leetcode.com/problems/remove-duplicates-from-sorted-list/)
- [82. Remove Duplicates from Sorted List II](https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/)
- [26. Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array)
- [80. Remove Duplicates from Sorted Array II](https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii)



## Remove Duplicates from Sorted List

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy(0);
        auto cur = &dummy;
        auto i = head;
        while (i != nullptr) {
            auto j = i;
            while (j != nullptr && j->val == i->val)
                j = j->next;

            cur->next = i, cur = cur->next;
            i = j;
        }
        cur->next = nullptr;
        return dummy.next;
    }
};
```



## Remove Duplicates from Sorted List II

Count the the number of duplicate node with same value.

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy(-1);
        auto cur = &dummy;
        ListNode *i = head, *j = nullptr;
        int cnt = 0;
        while (i != nullptr) {
            j = i;
            cnt = 0;
            while (j != nullptr && j->val == i->val)
                j = j->next, ++cnt;
            
            if (cnt == 1)
                cur->next = i, cur = cur->next;
            i = j;
        }
        cur->next = nullptr;
        return dummy.next;
    }
};
```



## Remove Duplicates from Sorted Array

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int idx = 1, n = nums.size();
        for (int i = 1; i < n; ++i)
            if (nums[i] != nums[i - 1])
                nums[idx++] = nums[i];
        return idx;
    }
};
```



## Remove Duplicates from Sorted Array II

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int idx = 0, n = nums.size(), i = 0;
        while (i < n) {
            int j = i;
            while (j < n && nums[j] == nums[i])
                ++j;
            
            int cnt = j - i;
            if (cnt == 1) nums[idx++] = nums[i];
            else nums[idx] = nums[idx + 1] = nums[i], idx += 2;
            
            i = j;
        }
        return idx;
    }
};
```

