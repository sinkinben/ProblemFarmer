/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include "leetcode.h"
class Solution
{
public:
    ListNode *swapPairs(ListNode *head)
    {
        ListNode *new_head = new ListNode(-1);
        new_head->next = head;
        help(new_head);
        head = new_head->next;
        return head;
    }

    void help(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
            return;
        ListNode *p, *q;
        p = head->next;
        q = p->next;
        p->next = q->next;
        q->next = p;
        head->next = q;
        help(p);
    }

    void print(ListNode *p)
    {
        while (p)
        {
            printf("%d ", p->val);
            p = p->next;
        }
        printf("\n");
    }
};