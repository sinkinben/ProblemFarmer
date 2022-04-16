## Nested List

Implement a nested list in C++, which is similar to list in python.



## List Node

First step is to define the `NestedNode`.

```cpp
struct NestedNode
{
    uint8_t islist;
    union {
        uint64_t uintval;
        NestedNode *list;
    } value;
    NestedNode *next;

    NestedNode(uint8_t islist, uint64_t data, NestedNode *next) : islist(islist), next(next)
    {
        value.uintval = data;
    }
};
```

- `islist = 1` denote the current node is a list.
- `union value` will store the data of current node - a integer or a pointer.
- `next` points to the next node.



## Nested List

And here is the nested list.

```cpp
class NestedList
{
  private:
    NestedNode *head;

    /* `head` should be dummy head pointer. */
    void DisplayNestedList(NestedNode *head)
    {
        cout << "[";
        for (auto p = head->next; p != nullptr; p = p->next)
        {
            if (!p->islist)
                cout << p->value.uintval;
            else
                DisplayNestedList(p->value.list);

            if (p->next)
                cout << ", ";
        }
        cout << "]";
    }

  public:
    NestedList() : head(new NestedNode(0, -1, nullptr)) {}

    /* Insert value at the front. */
    NestedNode *PushFront(uint64_t uintval) { return Insert(head, 0, uintval); }

    /* Insert list at the front. */
    NestedNode *PushFront(const NestedList &list)
    {
        assert(this != &list);
        return Insert(head, 1, (uint64_t)list.head);
    }

    /* Insert element after `pos`. */
    NestedNode *Insert(NestedNode *pos, uint8_t islist, uint64_t element)
    {
        assert(pos != nullptr && element != (uint64_t)(head));
        auto node = new NestedNode(islist, element, pos->next);
        pos->next = node;
        return node;
    }

    /* Display nested list. */
    void Display()
    {
        DisplayNestedList(head);
        cout << '\n';
    }

    /* Flattern the nested list in a non-recursive way. */
    vector<uint64_t> flattern()
    {
        vector<uint64_t> vec;
        stack<NestedNode *> stk;

        for (auto p = head->next; p != nullptr; p = p->next)
            stk.emplace(p);

        while (!stk.empty())
        {
            auto element = stk.top();
            stk.pop();

            if (element->islist)
            {
                for (auto p = element->value.list->next; p != nullptr; p = p->next)
                    stk.emplace(p);
            }
            else
                vec.emplace_back(element->value.uintval);
        }
        reverse(vec.begin(), vec.end());
        return vec;
    }
};
```

Here is the test code.

```cpp
NestedList generate(int l, int r)
{
    NestedList list;
    for (int i = l; i <= r; ++i)
        list.PushFront(i);
    return list;
}

int main()
{
    NestedList l1 = generate(0, 4), l2 = generate(5, 9);

    l1.Display();  // [4, 3, 2, 1, 0]
    l2.Display();  // [9, 8, 7, 6, 5]

    NestedList nested;
    nested.PushFront(l1);
    nested.Display();  // [[4, 3, 2, 1, 0]]

    for (int i = 10; i < 15; ++i)
        nested.PushFront(i);
    nested.PushFront(l2);
    nested.Display();  // [[9, 8, 7, 6, 5], 14, 13, 12, 11, 10, [4, 3, 2, 1, 0]]

    // 9 8 7 6 5 14 13 12 11 10 4 3 2 1 0
    auto vec = nested.flattern();
    for (uint64_t x : vec)
        cout << x << ' ';
}
```



## Nested Vector

It's similar to nested list above.

```cpp
struct NestedItem
{
    uint8_t nested = 0;
    union {
        uint64_t uintval = 0;
        vector<NestedItem> *vec;
    } value;
    NestedItem(uint8_t nested, uint64_t data) : nested(nested) { value.uintval = data; }
};
```

Here is the code of nested vector.

```cpp
class NestedVector
{
  private:
    vector<NestedItem> vec;
    void InternalDisplay(const vector<NestedItem> &list)
    {
        cout << "[";
        int n = list.size();
        for (int i = 0; i < n; ++i)
        {
            auto &item = list[i];
            if (item.nested)
                InternalDisplay(*(item.value.vec));
            else
                cout << item.value.uintval;
            if (i + 1 < n)
                cout << ", ";
        }
        cout << "]";
    }

  public:
    void PushBack(uint8_t nested, uint64_t data) { vec.emplace_back(nested, data); }

    void Display()
    {
        InternalDisplay(vec);
        cout << '\n';
    }

    vector<uint64_t> Falttern()
    {
        vector<uint64_t> res;
        stack<NestedItem> stk;
        for (auto &item : vec) stk.emplace(item);

        while (!stk.empty())
        {
            auto item = stk.top();
            stk.pop();

            if (item.nested)
                for (auto &x : *item.value.vec) stk.emplace(x);
            else
                res.emplace_back(item.value.uintval);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
```

Test code.

```cpp
NestedVector generate(int l, int r)
{
    NestedVector vec;
    for (uint64_t i = l; i <= r; ++i)
        vec.PushBack(0, i);
    return vec;
}

int main()
{
    NestedVector vec;
    auto v1 = generate(0, 2), v2 = generate(6, 9);

    v1.Display();  // [0, 1, 2]
    v2.Display();  // [6, 7, 8, 9]

    vec.PushBack(1, (uint64_t)&v1);
    for (uint64_t i = 3; i <= 5; ++i)
        vec.PushBack(0, i);
    vec.PushBack(1, (uint64_t)&v2);

    vec.Display();  // [[0, 1, 2], 3, 4, 5, [6, 7, 8, 9]]

    NestedVector vec2;
    vec2.PushBack(1, (uint64_t)&vec);
    vec2.PushBack(0, 999);
    vec2.Display();  // [[[0, 1, 2], 3, 4, 5, [6, 7, 8, 9]], 999]

    // 0 1 2 3 4 5 6 7 8 9 999
    auto flattern = vec2.Falttern();
    for (auto x : flattern)
        cout << x << ' ';
}
```



## Leetcode

- [385. Mini Parser](https://leetcode.com/problems/mini-parser/)
