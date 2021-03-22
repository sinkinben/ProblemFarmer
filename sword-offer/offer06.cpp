#include "../leetcode/leetcode.h"
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
    vector<int> reversePrint(ListNode *head)
    {
        vector<int> s;
        auto p = head;
        while (p!= nullptr)
            s.emplace_back(p->val), p = p->next;
        reverse(s.begin(), s.end());
        return s;
    }
};