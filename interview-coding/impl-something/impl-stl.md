## heap

To make a max-heap or min-heap, we need such operations: `heapify, make_heap, push_heap, pop_heap`.

The heap here is an array starts with index-0. And we **implement a max-heap** here.

<br/>

**heapify and make_heap**

- Time complexity of `heapify` is $O(\log{n})$.
- Time complexity of `make_heap` is $O(n)$ .

```cpp
/* Heapify from top to bottom. */
void heapify(vector<int> &vec, int idx)
{
    int n = vec.size();
    int l = 2 * idx + 1;
    int r = l + 1;
    int largest = idx;
    /* max-heap */
    if (l < n && vec[l] > vec[largest]) largest = l;
    if (r < n && vec[r] > vec[largest]) largest = r;
    if (largest != idx)
    {
        swap(vec[largest], vec[idx]);
        heapify(vec, largest);
    }
}
void make_heap(vector<int> &vec)
{
    /* [n/2 + 1, n) is the leaf nodes. */
    for (int i = vec.size() / 2; i >= 0; --i)
        heapify(vec, i);
}
```

<br/>

**pop_heap**

Time complexity of `pop_heap` should be $O(\log{n})$. 

In STL, we will pop a heap in such way:

```cpp
pop_heap(vec.begin(), vec.end());
int top = vec.back();
vec.pop_back();
```

Similar to above, we implement `pop_heap` in this way:

```cpp
/**
 * The input vector (in range [0, n - 1]) must be a heap.
 * Pop the heap, and return the top element. After this function,
 * the size of `heap` will decrease by 1.
 */
int pop_heap(vector<int> &heap)
{
    if (heap.empty()) return -1;
    int n = heap.size();
    swap(heap[0], heap[n - 1]);
    int top = heap.back();
    heap.pop_back();
    heapify(heap, 0);
    return top;
}
```



<br/>

**push_heap**

Time complexity of `push_heap` should be $O(\log{n})$. 

In STL, we will push an element into a heap in this way:

```cpp
vec.push_back(x);
push_heap(vec.begin(), vec.end());
```

Similar to the code above, we implement `push_heap` like this:

```cpp
/**
 * Push an new element into the heap. After this function,
 * the size of `heap` will increase by 1.
 */
void push_heap(vector<int> &heap, int x)
{
    int child, parent, n;
    heap.push_back(x);
    /* We need to adjust heap[n - 1] from bottom to top. */
    n = heap.size();
    child = n - 1, parent = (child - 1) / 2;
    /* max-heap */
    while (child > 0 && !(heap[child] < heap[parent]))
    {
        swap(heap[parent], heap[child]);
        child = parent;
        parent = (child - 1) / 2;
    }
}
```

<br/>

The code above `heapify, pop_heap, push_heap` is tested by:

```cpp
int main()
{
    vector<int> bench, heap;
    int N = 100000;
    srand(time(nullptr));
    for (int i = 0; i < N; ++i)
    {
        int op = random() % 2;
        if (op == 0)
        {
            int val = random();
            bench.push_back(val), push_heap(bench.begin(), bench.end());
            PushHeap(heap, val);
            assert(bench == heap);
        }
        else
        {
            if (bench.empty())
                continue;
            pop_heap(bench.begin(), bench.end());
            int val1 = bench.back();
            bench.pop_back();

            int val2 = PopHeap(heap);
            assert(val1 == val2);
        }
    }
}
```



## priority_queue

Based on `push_heap, pop_heap`, we can implement `priority_queue` (max-heap) like this.

```cpp
class priority_queue
{
  public:
    vector<int> heap;
    int top() { return !heap.empty() ? heap.front() : -1; }
    int pop() { return pop_heap(heap); }
    void push(int x) { push_heap(heap, x); }
};
```



## nth_element

```cpp
template< class RandomIt >
void nth_element( RandomIt first, RandomIt nth, RandomIt last );
```

Leetcode: [215. Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/).

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        int l = 0, r = n - 1;
        int target = n - k, pos = -1;
        do {
            pos = partition(nums, l, r);
            if (pos < target) l = pos + 1;
            else if (pos > target) r = pos - 1;
        } while (pos != target);
        return nums[target];
    }
    
    int partition(vector<int> &nums, int l, int r) {
        int key = nums[r];
        int j = l;
        for (int i = l; i < r; ++i)
            if (nums[i] < key)
                swap(nums[i], nums[j++]);
        /* pay attention to this, should not be nums[j++] */
        swap(nums[r], nums[j]);
        return j;
    }
};
```

For above algorithm, the **expectation** of time complexity is $O(N)$ .

If we use `nth_element` in STL, then

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) 
    {
        nth_element(nums.begin(), nums.begin() + k - 1, nums.end(), [](int a, int b) { return a > b; });
        return nums[k - 1];
    }
};
```





## next_permutation

Leetcode: [31. Next Permutation](https://leetcode.com/problems/next-permutation/)

- From right to left, find 1st position that satisfies `nums[i] < nums[i + 1]`.
- In range of `[i + 1, n)`, find the (right-most) min-value `nums[j]` among the elements who are `> nums[i]` .
- Swap `nums[i]` and `nums[j]`.
- Reverse the range `[i + 1, n)`.

```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return;

        int i = n - 2;
        while (i >= 0 && !(nums[i] < nums[i + 1])) --i;

        if (i >= 0)
        {
            int j = i + 1;
            for (int k = i + 1; k < n; ++k)
                if (nums[k] > nums[i] && nums[k] <= nums[j]) j = k;
            swap(nums[i], nums[j]);
        }
        reverse(nums.begin() + i + 1, nums.end());
    }
};
```



## iterator

Implement a iterator of vector.

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
template <typename T>
class Vector
{
public:
    class Iterator
    {
    public:
        // 标记 Iterator 是一个前向迭代器
        using iterator_category = std::forward_iterator_tag;
        // 表示 2 个迭代器之间的距离的数据类型, 由于我们这里是指针之间的距离, 所以使用整数或者 std::ptrdiff_t 均可
        using difference_type = uint32_t;
        // 类似于 typedef 
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        Iterator(pointer p) : ptr(p) {}
        reference operator*() const { return *ptr; }
        Iterator &operator++() { ptr++; return *this; }  // ++itor
        bool operator!=(Iterator &itor) const { return ptr != itor.ptr; }

    private:
        pointer ptr;
    };
    Vector(uint32_t n = 10) : size(n), data(new T[n]) {}
    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size); }

private:
    uint32_t size;
    T *data;
};
int main()
{
    Vector<int> v(5);
    int e = 0;
    for (auto &x : v) x = e++;
    for (auto &x : v) cout << x << ' ';
    cout << endl;
    
    std::fill(v.begin(), v.end(), 3);
    for (Vector<int>::Iterator x = v.begin(), end = v.end(); x != end; ++x)
        cout << *x << ' ';
}
```

