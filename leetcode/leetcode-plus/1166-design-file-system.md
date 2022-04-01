## Design File System

Leetcode: [1166. Design File System](https://leetcode-cn.com/problems/design-file-system/)

You are asked to design a file system that allows you to create new paths and associate them with different values.

The format of a path is one or more concatenated strings of the form: / followed by one or more lowercase English letters. For example, `"/leetcode"` and `"/leetcode/problems"` are valid paths while an empty string `""` and `"/"` are not.

Implement the `FileSystem` class:

- `bool createPath(string path, int value)` Creates a new `path` and associates a `value` to it if possible and returns true. Returns false if the path already exists or its parent path doesn't exist.
- `int get(string path)` Returns the value associated with `path` or returns -1 if the `path` doesn't exist.

<br/>

**Solution**

```cpp
struct FSNode
{
    int value;
    string name;
    map<string, FSNode *> children;
    FSNode(int v, const string &n) : value(v), name(n) {}
};
class FileSystem {
public:
    FSNode *root = new FSNode(-1, "/");
    FileSystem() {}
    
    vector<string> split(string &path) {
        vector<string> res = {"/"};
        if (path.empty()) return res;
        if (path.back() != '/') path.push_back('/');
        size_t pre = 1, pos = -1;
        while ((pos = path.find("/", pre)) != -1)
        {
            res.emplace_back(path.substr(pre, pos - pre));
            pre = pos + 1;
        }
        return res;
    }
    
    bool createPath(string path, int value) {
        auto vals = split(path);
        FSNode *ptr = root, *pre = nullptr;
        int n = vals.size();
        for (int i = 0; i + 1 < n; ++i)
        {
            /* parent path doesn't exist. */
            if (ptr == nullptr || vals[i] != ptr->name) return false;
            pre = ptr;
            ptr = ptr->children[vals[i + 1]];
        }
        /* total path has existed. */
        if (ptr) return false;
        pre->children[vals[n - 1]] = new FSNode(value, vals[n - 1]);
        return true;
    }
    
    int get(string path) {
        auto vals = split(path);
        FSNode *ptr = root;
        int n = vals.size();
        for (int i = 0; i + 1 < n; ++i)
        {
            if (ptr == nullptr || vals[i] != ptr->name) return -1;
            ptr = ptr->children[vals[i + 1]];
        }
        return ptr == nullptr ? -1 : ptr->value;
    }
};
```

