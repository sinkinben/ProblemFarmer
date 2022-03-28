## skiplist

"Skip List"，即「跳表」，是 redis 的核心数据结构，可在 $O(\log{n})$ 的时间复杂度内完成「增删改查」四项基本操作。

<img src="https://assets.leetcode.com/uploads/2019/09/27/1506_skiplist.gif" style="width: 60%"/>

```cpp

class skiplist {
private:
    struct node_t {
        int val;
        node_t *right, *down;
        node_t(int val = 0, node_t *right = nullptr, node_t *down = nullptr)
            : val(val), right(right), down(down) {}
    };

public:
    node_t *head;
    skiplist() { head = new node_t(); }

    bool search(int val) { return inner_search(val) != nullptr; }

    node_t *inner_search(int val) {
        auto p = head;

        /* This while-loop is similar in `add` and `erase`,
         * it aims to find the target `val`.
         */
        while (p) {
            while (p->right && p->right->val < val)
                p = p->right;
            if (!(p->right) || p->right->val > val)
                p = p->down;
            else
                return p->right;
        }
        return nullptr;
    }

    void add(int val) {
        vector<node_t *> insert_points;
        auto p = head;
        while (p) {
            while (p->right && p->right->val < val)
                p = p->right;
            insert_points.push_back(p);
            p = p->down;
        }

        node_t *down_node = nullptr;
        bool insert_up = true;
        while (insert_up && !insert_points.empty()) {
            auto point = insert_points.back();
            insert_points.pop_back();

            point->right = new node_t(val, point->right, down_node);
            down_node = point->right;
            /* Probability of 0.5, to determine whether if to insert new node `val`
             * in each layer.
             */
            insert_up = (rand() & 1);
        }

        /* This will cause the level of skiplist up. */
        if (insert_up)
            head = new node_t(0, new node_t(val, nullptr, down_node), head);
    }

    bool erase(int val) {
        auto p = head;
        bool seen = false;
        while (p) {
            while (p->right && p->right->val < val)
                p = p->right;
            if (!(p->right) || p->right->val > val)
                p = p->down;
            else {
                /* target val is stored in node `p->right` */
                seen = true;
                auto next = p->right->right;
                delete p->right;
                p->right = next;
                p = p->down;
            }
        }
        return seen;
    }
};
```



[Leetcode - skiplist](https://leetcode.com/problems/design-skiplist/).