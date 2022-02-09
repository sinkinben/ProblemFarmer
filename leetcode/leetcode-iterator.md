## Iterator

Problems:

- [173. Binary Search Tree Iterator](https://leetcode.com/problems/binary-search-tree-iterator)
- [1586. Binary Search Tree Iterator II](https://leetcode.com/problems/binary-search-tree-iterator-ii)



## BST Iterator

Implement the `BSTIterator` class that represents an iterator over the **[in-order traversal](https://en.wikipedia.org/wiki/Tree_traversal#In-order_(LNR))** of a binary search tree (BST):

- `BSTIterator(TreeNode root)` Initializes an object of the `BSTIterator` class. The `root` of the BST is given as part of the constructor. The pointer should be initialized to a non-existent number smaller than any element in the BST.
- `boolean hasNext()` Returns `true` if there exists a number in the traversal to the right of the pointer, otherwise returns `false`.
- `int next()` Moves the pointer to the right, then returns the number at the pointer.

Notice that by initializing the pointer to a non-existent smallest number, the first call to `next()` will return the smallest element in the BST.

You may assume that `next()` calls will always be valid. That is, there will be at least a next number in the in-order traversal when `next()` is called.

**Example**

```text
Input
["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
[[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
Output
[null, 3, 7, true, 9, true, 15, true, 20, false]

Explanation
BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
bSTIterator.next();    // return 3
bSTIterator.next();    // return 7
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 9
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 15
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 20
bSTIterator.hasNext(); // return False
```

<br/>

**Solution**

```cpp
class BSTIterator {
protected:
    stack<TreeNode*> stk;
public:
    BSTIterator(TreeNode* root) { pushLeft(root); }
    
    int next() {
        auto ptr = stk.top();
        stk.pop();
        pushLeft(ptr->right);
        return ptr->val;
    }
    
    bool hasNext() { return !stk.empty(); }
    
    void pushLeft(TreeNode *p) {
        while (p) {
            stk.emplace(p);
            p = p->left;
        }
    }
};
```



## BST Iterator II

Implement the `BSTIterator` class that represents an iterator over the **[in-order traversal](https://en.wikipedia.org/wiki/Tree_traversal#In-order_(LNR))** of a binary search tree (BST):

- `BSTIterator(TreeNode root)` Initializes an object of the `BSTIterator` class. The `root` of the BST is given as part of the constructor. The pointer should be initialized to a non-existent number smaller than any element in the BST.
- `boolean hasNext()` Returns `true` if there exists a number in the traversal to the right of the pointer, otherwise returns `false`.
- `int next()` Moves the pointer to the right, then returns the number at the pointer.
- `boolean hasPrev()` Returns `true` if there exists a number in the traversal to the left of the pointer, otherwise returns `false`.
- `int prev()` Moves the pointer to the left, then returns the number at the pointer.

Notice that by initializing the pointer to a non-existent smallest number, the first call to `next()` will return the smallest element in the BST.

You may assume that `next()` and `prev()` calls will always be valid. That is, there will be at least a next/previous number in the in-order traversal when `next()`/`prev()` is called.

**Follow up:** Could you solve the problem without precalculating the values of the tree?

**Example**

<img src="https://assets.leetcode.com/uploads/2020/09/14/untitled-diagram-1.png" />

```text
Input
["BSTIterator", "next", "next", "prev", "next", "hasNext", "next", "next", "next", "hasNext", "hasPrev", "prev", "prev"]
[[[7, 3, 15, null, null, 9, 20]], [null], [null], [null], [null], [null], [null], [null], [null], [null], [null], [null], [null]]
Output
[null, 3, 7, 3, 7, true, 9, 15, 20, false, true, 15, 9]

Explanation
// The underlined element is where the pointer currently is.
BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]); // state is   [3, 7, 9, 15, 20]
bSTIterator.next(); // state becomes [3, 7, 9, 15, 20], return 3
bSTIterator.next(); // state becomes [3, 7, 9, 15, 20], return 7
bSTIterator.prev(); // state becomes [3, 7, 9, 15, 20], return 3
bSTIterator.next(); // state becomes [3, 7, 9, 15, 20], return 7
bSTIterator.hasNext(); // return true
bSTIterator.next(); // state becomes [3, 7, 9, 15, 20], return 9
bSTIterator.next(); // state becomes [3, 7, 9, 15, 20], return 15
bSTIterator.next(); // state becomes [3, 7, 9, 15, 20], return 20
bSTIterator.hasNext(); // return false
bSTIterator.hasPrev(); // return true
bSTIterator.prev(); // state becomes [3, 7, 9, 15, 20], return 15
bSTIterator.prev(); // state becomes [3, 7, 9, 15, 20], return 9
```

<br/>

**Solution**

- Similar to "BST Iterator" above, we use stack `stk` to implement inorder traversal.
- At the same time, use a vector `vec` to stored those nodes we have been visited.
- When access `next/prev`, we access the nodes in `vec` firstly.

```cpp
class BSTIterator {
public:
    vector<TreeNode*> vec;
    stack<TreeNode*> stk;
    int cursor = -1;
    BSTIterator(TreeNode* root) { pushLeft(root); }

    void pushLeft(TreeNode *p) {
        while (p) {
            stk.push(p);
            p = p->left;
        }
    }

    bool validCursor(int cursor) { return 0 <= cursor && cursor < (int)vec.size(); }
    
    bool hasNext() {
        if (validCursor(cursor + 1))
            return true;
        return !stk.empty();
    }
    
    int next() {
        if (validCursor(cursor + 1)) {
            return vec[++cursor]->val;
        } else {
            auto p = stk.top();
            stk.pop();
            vec.emplace_back(p), ++cursor; /* cursor should be kept at the top */
            pushLeft(p->right);
            return p->val;
        }
    }
    
    bool hasPrev() { return validCursor(cursor - 1); }
    
    int prev() { return vec[--cursor]->val; }
};
```

