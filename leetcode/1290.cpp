#include "leetcode.h"
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution
{
public:
    int getDecimalValue(struct ListNode *head)
    {
        int n = 0;
        auto p = head;
        while (p)
        {
            n |= p->val;
            n <<= 1;
            p = p->next;
        }
        return n;
    }
};

int main()
{
}