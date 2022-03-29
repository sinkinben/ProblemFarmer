## High Five

Leetcode: [1086. High Five](https://leetcode-cn.com/problems/high-five/)

Given a list of the scores of different students, `items`, where `items[i] = [IDi, scorei]` represents one score from a student with `IDi`, calculate each student's top five average.

Return the answer as an array of pairs result, where `result[j] = [IDj, topFiveAveragej]` represents the student with `IDj` and their top five average. Sort result by `IDj` in increasing order.

A student's top five average is calculated by taking the sum of their top five scores and dividing it by 5 using integer division.

 **Solution**

For each student, push all scores into max-heap, and then get the firstly five scores.

```cpp
class Solution {
public:
    vector<vector<int>> highFive(vector<vector<int>>& items) {
        map<int, priority_queue<int>> table;
        for (auto &vec : items)
        {
            int id = vec[0];
            table[id].emplace(vec[1]);
        }
        vector<vector<int>> res;
        for (auto &[id, scores] : table)
        {
            int sum = 0;
            for (int i = 0; i < 5; ++i) sum += scores.top(), scores.pop();
            res.emplace_back(vector{id, sum / 5});
        }
        return res;
    }
};
```



