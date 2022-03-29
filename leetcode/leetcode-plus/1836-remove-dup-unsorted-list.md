## Remove Duplicates From an Unsorted Linked List

Leetcode: [1836. Remove Duplicates From an Unsorted Linked List](https://leetcode-cn.com/problems/remove-duplicates-from-an-unsorted-linked-list/)

Given the `head` of a linked list, find all the values that appear more than once in the list and delete the nodes that have any of those values.

Return the linked list after the deletions.

```text
Input: head = [1,2,3,2]
Output: [1,3]
Explanation: 2 appears twice in the linked list, so all 2's should be deleted. After deleting all 2's, we are left with [1,3].
```

**Solution**

```cpp
class Solution {
public:
    ListNode* deleteDuplicatesUnsorted(ListNode* head) {
        unordered_map<int, int> cnt;
        for (auto p = head; p != nullptr; p = p->next)
            ++cnt[p->val];
        ListNode dummy(0, nullptr);
        auto cur = &dummy;
        for (auto p = head; p != nullptr; p = p->next)
            if (cnt[p->val] == 1)
                cur->next = p, cur = cur->next;
        cur->next = nullptr;
        return dummy.next;
    }
};
```

