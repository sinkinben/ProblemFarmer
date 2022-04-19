## Ring Queue

Implement a ring buffer (ring queue) without STL.

```cpp
class RingQueue
{
  protected:
    int *buffer;
    int in, out;
    int capacity;

  public:
    RingQueue(int cap = 16) : in(0), out(0), capacity(cap + 1), buffer(new int[cap + 1]) {}
    ~RingQueue() { delete[] buffer; }

    bool Full() { return ((in + 1) % capacity) == out; }
    bool Empty() { return in == out; }
    bool Put(int item)
    {
        if (Full()) return false;
        buffer[in] = item;
        in = (in + 1) % capacity;
        return true;
    }
    int Get()
    {
        if (Empty()) return -1;
        int item = buffer[out];
        out = (out + 1) % capacity;
        return item;
    }

    void Display()
    {
        printf("full: %d, empty: %d, data: ", Full(), Empty());
        for (int i = out; i != in; i = (i + 1) % capacity)
            cout << buffer[i] << ' ';
        cout << '\n';
    }
};

/* Test Code */
int main()
{
    RingQueue rq(3);
    printf("%d %d %d\n", rq.Put(11), rq.Put(22), rq.Put(33));
    rq.Display();

    cout << rq.Get() << '\n';
    rq.Display();

    rq.Put(44);
    rq.Display();

    printf("%d %d %d\n", rq.Get(), rq.Get(), rq.Get());

    rq.Display();
}
```

