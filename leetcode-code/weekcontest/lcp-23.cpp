#include "../leetcode.h"
class Solution
{
public:
    int firstMatch = -1;
    bool isMagic(vector<int> &target)
    {
        int n = target.size();
        vector<int> cards(n, 0);
        for (int i = 0; i < n; i++)
            cards[i] = i + 1;
        return shuffle(cards, target, 0);
    }

    bool shuffle(vector<int> &cards, const vector<int> &target, const int idx)
    {
        if (idx == (int)cards.size())
            return true;
        vector<int> tmp(cards);
        int size = tmp.size();
        int i = idx, j = idx + 1;
        for (; j < size; j += 2, i++)
            cards[i] = tmp[j];
        j = idx;
        for (; j < size; i++, j += 2)
            cards[i] = tmp[j];
        i = idx;
        while (i < size && target[i] == cards[i])
            i++;
        if (i == size)
            return true;

        int match = i - idx;
        if (firstMatch == -1)
            firstMatch = match;
        if (match == 0 || match < firstMatch)
            return false;

        return shuffle(cards, target, i);
    }
};

int main()
{
    vector<int> v1 = {2, 4, 3, 1, 5};
    vector<int> v = {2, 4, 6, 10, 14, 18,
                     26, 34, 42, 15, 31, 8,
                     40, 29, 38, 20, 41, 16,
                     35, 13, 36, 12, 23, 24,
                     37, 30, 28, 27, 17, 22,
                     25, 7, 1, 9, 11, 21,
                     5, 19, 43, 33, 32, 39, 3};
    vector<int> v2 = {5, 4, 3, 2, 1};
    Solution sol;
    cout << sol.isMagic(v2) << endl;
}