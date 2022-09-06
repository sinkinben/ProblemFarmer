## Implement shared_ptr

```cpp
#include <functional>
#include <iostream>
template <class T> struct DefaultDeleter {
    void operator()(T *p) { delete p; }
};
template <class T, class Deleter = DefaultDeleter<T>> class shared_pointer {
  private:
    T *ptr;
    uint32_t *refcnt;
    Deleter deleter;

  public:
    /* default ctor */
    shared_pointer() : ptr(nullptr), refcnt(new uint32_t(1)) {}

    /* ctor */
    shared_pointer(T *p) : ptr(p), refcnt(new uint32_t(1)) {}

    /* copy ctor */
    shared_pointer(const shared_pointer &sptr) {
        ptr = sptr.ptr;
        refcnt = sptr.refcnt;
        if (ptr != nullptr) {
            ++(*refcnt);
        }
    }

    /* move ctor */
    shared_pointer(shared_pointer &&sptr) {
        ptr = sptr.ptr, refcnt = sptr.refcnt;
        sptr.ptr = nullptr, sptr.refcnt = nullptr;
    }

    /* copy assignment */
    shared_pointer &operator=(const shared_pointer &sptr) {
        if (this == &sptr)
            return *this;
        clear();
        ptr = sptr.ptr, refcnt = sptr.refcnt;
        if (ptr != nullptr) {
            ++(*refcnt);
        }
        return *this;
    }

    /* move assignment */
    shared_pointer &operator=(shared_pointer &&sptr) {
        if (this == &sptr)
            return *this;
        clear();
        ptr = sptr.ptr, refcnt = sptr.refcnt;
        sptr.ptr = nullptr, sptr.refcnt = nullptr;
        return *this;
    }

    uint32_t get_count() const { return *refcnt; }
    T *operator->() const { return ptr; }
    virtual ~shared_pointer() { if (refcnt != nullptr) clear(); }

  private:
    void clear() {
        --(*refcnt);
        if ((*refcnt) == 0) {
            if (ptr != nullptr) {
                deleter(ptr);
            }
            delete refcnt;
            ptr = nullptr, refcnt = nullptr;
        }
    }
};
class Box {
  public:
    void print() { std::cout << "Box::print()\n"; }
    virtual ~Box() {}
};
struct mydeleter {
    void operator()(Box *ptr) { delete[] ptr; }
};
int main() {
    {
        shared_pointer<Box, mydeleter> sptr(new Box[3]);
        sptr = sptr;
        std::cout << sptr.get_count() << "\n"; // 1
        sptr->print();                         // Box::print()
    }
    {
        shared_pointer<Box> sptr(new Box());
        shared_pointer<Box> sptr2(sptr);
        shared_pointer<Box> sptr3(std::move(sptr2));
        std::cout << sptr.get_count() << "\n"; // 2
        sptr->print();                         // Box::print()
    }
}
```



## Implement unique_ptr

https://codereview.stackexchange.com/questions/163854/my-implementation-for-stdunique-ptr

- Copy-contructor should be `= delete`, and the overload function `operator=` should be `= delete`.

  ```cpp
  unique_ptr(unique_ptr const&) = delete;
  unique_ptr& operator=(unique_ptr const&) = delete;
  ```



