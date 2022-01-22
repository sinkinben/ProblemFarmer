## [leetcode] K 个一组翻转链表

题目：[25. K 个一组翻转链表](https://leetcode-cn.com/problems/reverse-nodes-in-k-group/)

先看怎么反转链表（写不出来的话，我建议你爪巴）：

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) return nullptr;
        auto pre = head, cur = head->next;
        while (cur != nullptr)
        {
            auto next = cur->next;
            cur->next = pre;
            pre = cur, cur = next;
        }
        head->next = nullptr;
        return pre;
    }
};
```



第一步，实现一个 K 个反转的函数，把 `[head, tail]` 区间内的节点反转（与上面的反转链表一毛一样），返回子链表的**新的头和尾**。

```cpp
pair<ListNode*, ListNode*> helper(ListNode* const head, ListNode* const tail)
{
    auto pre = head, cur = head->next;
    auto end = tail->next;
    while (cur != end)
    {
        auto next = cur->next;
        cur->next = pre;
        pre = cur, cur = next;
    }
    head->next = end;
    return {tail, head};
}
```



第二步，我们先看看一个例子。

```
K = 3, list = [1 2 3 4 5 6]

// 添加一个 dummy 节点
-1 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6
    
// 变量指向
pre  head      tail next
 |    |         |    |
 V    V         V    V
-1    1 -> 2 -> 3    4 -> 5 -> 6

// 执行 (head, tail) = helper(head, tail) 后
pre  head      tail next
 |    |         |    |
 V    V         V    V
-1    3 -> 2 -> 1    4 -> 5 -> 6

// 重新「插入」子链表
pre  head      tail next
 |    |         |    |
 V    V         V    V
-1 -> 3 -> 2 -> 1 -> 4 -> 5 -> 6

// 然后调整 [head, tail] 区间，继续执行 helper
               pre  head      tail  next
                |    |         |     |
                V    V         V     V
-1 -> 3 -> 2 -> 1 -> 4 -> 5 -> 6 -> null
```



然后就可以写出主循环了：

```cpp
ListNode* reverseKGroup(ListNode* head, int k) 
{
    if (head == nullptr || head->next == nullptr) return head;

    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    auto pre = dummy;
    while (head != nullptr)
    {
        auto tail = pre;
        for (int i=0; i<k; i++)
        {
            tail = tail->next;
            // 如果不够 K 个
            if (tail == nullptr) return dummy->next;
        }
        auto next = tail->next;
        tie(head, tail) = helper(head, tail);
        // 「插入」子链表
        pre->next = head, tail->next = next;
        // 区间移动
        pre = tail, head = tail->next;
    }
    return dummy->next;
}
```



👴 觉得这个常数空间的解法太阴间了，自己写好多细节都会出问题，所以用栈试试。

这下子代码就好看得多了。

```cpp
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) 
    {
        ListNode dummy(-1);
        auto cur = &dummy;
        auto p = head;
        while (p)
        {
            vector<ListNode*> buf;
            for (int i=0; i<k && p != nullptr; i++)
                buf.push_back(p), p = p->next;
            // 不足 K 个，直接连上后续的
            if (buf.size() < k)
            {
                cur->next = buf[0];
                break;
            }
            for (int i=buf.size()-1; i>=0; i--)
                cur->next = buf[i], cur = cur->next;
            // 防止出现环，e.g. k=2, list = [1, 2]
           	cur->next = nullptr;
        }
        return dummy.next;
    }
};
```

