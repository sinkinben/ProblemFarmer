#include "leetcode.h"
#include <list>
#include <unordered_map>
struct node_t
{
    int key, val;
    node_t(int k, int v) : key(k), val(v) {}
};
class LRUCache
{
public:
    list<node_t> cache;
    unordered_map<int, list<node_t>::iterator> table;
    int capacity;
    LRUCache(int capacity)
    {
        this->capacity = capacity;
    }

    int get(int key)
    {
        if (table.count(key))
        {
            node_t node = *table[key];
            cache.erase(table[key]);
            cache.emplace_front(node);
            table[key] = cache.begin();
            return node.val;
        }
        return -1;
    }

    void put(int key, int value)
    {
        if (table.count(key) != 0)
        {
            cache.erase(table[key]);
            cache.emplace_front(node_t(key, value));
            table[key] = cache.begin();
        }
        else
        {
            cache.emplace_front(node_t(key, value));
            table[key] = cache.begin();
            if ((int) cache.size() ==  capacity + 1)
            {
                node_t node = cache.back();
                cache.pop_back();
                table.erase(node.key);
            }
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */