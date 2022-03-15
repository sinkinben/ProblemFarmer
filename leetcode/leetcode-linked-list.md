## Linked List Problems

- [206. Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/)
- [92. Reverse Linked List II](https://leetcode.com/problems/reverse-linked-list-ii/)
- [25. Reverse Nodes in k-Group](https://leetcode.com/problems/reverse-nodes-in-k-group/)



## Reversed Linked List

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *cur = head, *pre = nullptr;
        while (cur) {
            auto next = cur->next;
            cur->next = pre;
            pre = cur, cur = next;
        }
        return pre;
    }
};
```



## Reversed Linked List II

**Two Passes**

- K 个一组反转链表的 Mini 版本

```cpp
class Solution {
public:
    pair<ListNode*, ListNode*> rangeReverse(ListNode *head, ListNode *tail) {
        if (head == nullptr || tail == nullptr) return {head, tail};
        auto end = tail->next;
        auto pre = end, cur = head;
        while (cur != end) {
            auto next = cur->next;
            cur->next = pre;
            pre = cur, cur = next;
        }
        return {tail, head};
    }

    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode dummy(0, head);
        auto p = head, q = head, pre = &dummy;
        for (int i = 1; i < left; ++i) pre = p, p = p->next;
        
        q = p;
        for (int i = 0; i < right - left; ++i) q = q->next;
        
        auto next = q ? q->next : nullptr;
        auto [p1, p2] = rangeReverse(p, q);
        pre->next = p1, p2->next = next;
        return dummy.next;
    }
};
```

**Only One Pass**

- 先找到 `left` 所在位置，然后反转链表 `right - left` 次。
- 「反转」操作略有不同，因为无法得知链表的结束位置，而是通过 `for` 来控制反转的次数。

```cpp
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode dummy(0, head);
        ListNode *pre = &dummy, *p = head;
        for (int i = 1; i < left; ++i)
            pre = p, p = p->next;
        
        ListNode *tmp = nullptr, *next = p->next;
        for (int i = 0; (i < right - left) && p; ++i) {
            tmp = p;
            p = next;
            
            next = p->next;
            p->next = tmp;
        }
        if (pre->next)
            pre->next->next = next;
        pre->next = p;
        return dummy.next;
    }
};
```



## Reverse Nodes in k-Group

```cpp
class Solution {
public:
    pair<ListNode*, ListNode*> rangeReverse(ListNode *head, ListNode *tail) {
        if (head == nullptr || tail == nullptr || head == tail)
            return {head, tail};
        auto end = tail->next;
        auto pre = end, cur = head;
        while (cur != end) {
            auto next = cur->next;
            cur->next = pre;
            pre = cur, cur = next;
        }
        return {tail, head};
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0, head);
        auto pre = &dummy;
        
        while (pre != nullptr) {
            auto head = pre->next;
            auto tail = pre;
            for (int i = 0; i < k; ++i) {
                tail = tail->next;
                if (tail == nullptr)
                    return dummy.next;
            }
            auto next = tail ? tail->next : nullptr;
            tie(head, tail) = rangeReverse(head, tail);
            pre->next = head, tail->next = next;
            pre = tail;
        }
        
        return dummy.next;
    }
};
```

