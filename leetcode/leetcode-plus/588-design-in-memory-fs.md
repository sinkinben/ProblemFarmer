## Design In-Memory File System

Leetcode: [588. Design In-Memory File System](https://leetcode-cn.com/problems/design-in-memory-file-system/)

Design a data structure that simulates an in-memory file system.

Implement the FileSystem class:

- `FileSystem()` Initializes the object of the system.
- `List<String> ls(String path)`
  - If `path` is a file path, returns a list that only contains this file's name.
  - If `path` is a directory path, returns the list of file and directory names in this directory.
  - The answer should in **lexicographic order**.
- `void mkdir(String path)` Makes a new directory according to the given `path`. The given directory `path` does not exist. If the middle directories in the path do not exist, you should create them as well.
- `void addContentToFile(String filePath, String content)`
  - If `filePath` does not exist, creates that file containing given `content`.
  - If `filePath` already exists, appends the given `content` to original content.
- `String readContentFromFile(String filePath)` Returns the content in the file at filePath.

<img src="https://assets.leetcode.com/uploads/2021/04/28/filesystem.png" style="width:70%" />

**Solution**

- Organize all files (including directories and common files) into a tree (which is similar to Trie Tree).
- Since `ls` require a lexicographic order, we use `map<>` to store the children. `map<>` will sort the names automatically.

```cpp
enum FSType
{
    DIR = 0,
    FLE
};
struct FSNode
{
    FSType fstype;
    string name;
    string content;                    /* file content, fstype = FLE */
    map<string, FSNode *> children;    /* dir content, fstype = DIR */
    FSNode(FSType t, const string &n) : fstype(t), name(n) {}
};
class FileSystem {
protected:
    FSNode *root = new FSNode(FSType::DIR, "/");
    
    /* Split the path into a list. e.g. "/a/b/c" -> ["/", "a", "b", "c"]
     * It requires that the path is valid.
     */
    vector<string> split(string &path)
    {
        assert(!path.empty());
        if (path.back() != '/') path.push_back('/');

        vector<string> res = {"/"};
        size_t n = path.length();
        size_t pre = 1, pos = -1;
        while ((pos = path.find("/", pre)) != -1)
        {
            res.emplace_back(path.substr(pre, pos - pre));
            pre = pos + 1;
        }
        return res;
    }
public:
    
    FileSystem() {}
    
    vector<string> ls(string path) {
        auto ptr = getLastChild(path);
        if (ptr->fstype == FSType::FLE)
            return { ptr->name };
        vector<string> res;
        for (auto &[name, child]: ptr->children)
            res.emplace_back(name);
        return res;
    }
    
    void mkdir(string path) {
        auto vals = split(path);
        auto ptr = root;
        int n = vals.size();
        for (int i = 0; i + 1 < n; ++i)
        {
            assert(vals[i] == ptr->name);
            if (ptr->children.count(vals[i + 1]) == 0)
                ptr->children[vals[i + 1]] = new FSNode(DIR, vals[i + 1]);
            ptr = ptr->children[vals[i + 1]];
        }
    }
    
    /* Get last child according to the path. e.g. "/a/b/c", it returns the
     * pointer of file `c`. If `c` doesn't exist, create it and return.
     * It requires the previous directories must exists, i.e. ["/", "a", "b"]
     * must exist, otherwise it fails.
     */
    FSNode *getLastChild(string &path) {
        auto vals = split(path);
        FSNode *ptr = root, *pre = nullptr;
        int n = vals.size();
        for (int i = 0; i + 1 < n; ++i)
        {
            assert(ptr != nullptr);
            if (vals[i] == ptr->name)
            {
                pre = ptr;
                ptr = ptr->children[vals[i + 1]];
            }
        }
        if (ptr == nullptr)
            ptr = pre->children[vals[n - 1]] = new FSNode(FSType::FLE, vals[n - 1]);
        return ptr;
    }
    
    string readContentFromFile(string path) {
        auto ptr = getLastChild(path);
        assert(ptr->fstype == FSType::FLE);
        return ptr->content;
    }

    void addContentToFile(string path, string content) {
        auto ptr = getLastChild(path);
        assert(ptr->fstype == FSType::FLE);
        ptr->content += content;
    }
};
```

