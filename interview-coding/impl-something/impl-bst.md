## Implement BST

- [450. Delete Node in a BST](https://leetcode.com/problems/delete-node-in-a-bst)
- [701. Insert into a Binary Search Tree](https://leetcode.com/problems/insert-into-a-binary-search-tree)
- [700. Search in a Binary Search Tree](https://leetcode.com/problems/search-in-a-binary-search-tree/)

实际面试中，可能要求手写 `remove, insert, search` 这三个操作，因此这里总结了一个比较适用于面试的版本。

```cpp
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
template <class T, class Comparator = less<T>> class BST {
public:
    struct TreeNode {
        T value;
        TreeNode *left, *right;
        TreeNode(T v) : value(v), left(nullptr), right(nullptr) {}
    };

public:
    BST() : root(nullptr) {}

    /* Of course, we can implement insert in a recursive way,
     * but I think iteration is better to understand
     */
    TreeNode *insert(const T &value) {
        auto node = new TreeNode(value);
        if (root == nullptr)
            return root = node;
        TreeNode *ptr = root, *pre = nullptr;
        while (ptr) {
            pre = ptr;
            if (cmp(value, ptr->value)) // value < ptr->value
                ptr = ptr->left;
            else if (cmp(ptr->value, value)) // ptr->value < value
                ptr = ptr->right;
            else {
                // value == ptr->value, value has existed already.
                delete node;
                return nullptr;
            }
        }
        assert(pre != nullptr);
        return (cmp(value, pre->value) ? pre->left : pre->right) = node;
    }

    TreeNode *search(const T &value) {
        auto ptr = root;
        while (ptr) {
            if (cmp(value, ptr->value)) // value < ptr->value
                ptr = ptr->left;
            else if (cmp(ptr->value, value)) // ptr->value < value
                ptr = ptr->right;
            else
                break;
        }
        return ptr;
    }

    void remove(const T &value) { root = remove(root, value); }

    virtual ~BST() {
        destroy(root);
        root = nullptr;
    }

    vector<T> inorder() {
        vector<T> vec;
        inorder(root, vec);
        return vec;
    }

private:
    /* destroy by post-order */
    void destroy(TreeNode *node) {
        if (node == nullptr)
            return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    /* display by in-order */
    void inorder(TreeNode *node, vector<T> &vec) {
        if (node == nullptr)
            return;
        inorder(node->left, vec);
        vec.emplace_back(node->value);
        inorder(node->right, vec);
    }

    /* innerRemove - remove value from BST by recursion */
    TreeNode *remove(TreeNode *node, const T &value) {
        if (node == nullptr)
            return node;

        if (cmp(value, node->value)) // value < node->value
            node->left = remove(node->left, value);
        else if (cmp(node->value, value)) // node->value < value
            node->right = remove(node->right, value);
        else {
            /* Leaf node */
            if (!(node->left) && !(node->right)) {
                delete node;
                return nullptr;
            }
            /* Only one child */
            if (!(node->left) || !(node->right)) {
                TreeNode *ret = (node->left) ? (node->left) : (node->right);
                delete node;
                return ret;
            }
            /* Two children - find the minval of right-subtree (successor),
             * replace value of node with successor->value,
             * delete successor->value recursively
             */
            if (node->left && node->right) {
                auto suc = successor(node);
                node->value = suc->value;
                node->right = remove(node->right, suc->value);
                return node;
            }
        }
        return node;
    }

    TreeNode *successor(TreeNode *node) {
        assert(node != nullptr && node->right != nullptr);
        node = node->right;
        while (node->left)
            node = node->left;
        return node;
    }

private:
    TreeNode *root;
    Comparator cmp;
};
```

测试代码：

```cpp
int main() {
    clock_t start = clock();

    srand(time(nullptr));
    const int n = 10000;
    BST<int> bst;
    for (int i = 0; i < n; ++i)
        bst.insert(i);
    auto vec = std::move(bst.inorder());
    unordered_set<int> bench(vec.begin(), vec.end());

    while (!bench.empty()) {
        int val = rand() % n;
        if (!bench.count(val))
            continue;
        bst.remove(val);
        bench.erase(val);
        vec = std::move(bst.inorder());
        assert(unordered_set<int>(vec.begin(), vec.end()) == bench);
    }

    clock_t end = clock();

    printf("Insert [0, %d) and remove all of them. \n", n);
    printf("Total cost %lf seconds. \n",
           ((double)(end)-start) / CLOCKS_PER_SEC);
}
```

