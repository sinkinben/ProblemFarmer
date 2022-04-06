## [leetcode] 二叉树的序列化与反序列化

题目来源：https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/ .

按照 Leetcode 的官方习惯，二叉树的序列化逻辑是根据其「层次遍历」序列来实现的（参考[该文章](https://support.leetcode-cn.com/hc/kb/article/1194353/)），因此本文以这种方式来解题。

## 预备工作

对于反序列化过程，其输入是一个字符串，我们需要将其转换为 `vector<string>` ，如 `"1,null,2"` 需要转换为 `{"1", "null", 2"}` .

```cpp
vector<string> split(string &data, const string &sep)
{
    size_t l = 0;
    size_t r = data.find(sep, l);
    vector<string> result;
    while (r != string::npos)
    {
        result.emplace_back(data.substr(l, r - l));
        l = r + sep.length();
        r = data.find(sep, l);
    }
    if (l < data.length())
        result.emplace_back(data.substr(l));
    return result;
}
```

对于 `vector<string>` 中的每个元素，构造一个 API，返回对应的二叉树节点（包括空节点）：

```cpp
TreeNode *generateNode(const string &s)
{
    return s == NIL ? nullptr : new TreeNode(stoi(s));
}
```

其次，需要 2 个常量（以成员变量的形式存在），`NIL` 是空节点的符号表示，`SEPARATOR` 是序列化字符串中的分隔符：

```cpp
const string NIL = "null";
const string SEPARATOR = ",";
```

## 层次遍历实现

+ **序列化**

与一般的层次遍历几乎一样，唯一不同的地方是：**在此处，空节点 `nullptr` 也进入队列当中** 。

❗ 需要注意的是：最后一层均为**叶子节点**，因此它们的左右孩子均为 `null` ，按照 Leetcode 的要求，序列化字符串中不包含这些最后一层叶子节点的孩子。

```cpp
string levelSerialize(TreeNode *root)
{
    if (root == nullptr)
        return "";
    queue<TreeNode *> q;
    q.push(root);
    vector<string> result;
    while (!q.empty())
    {
        auto node = q.front();
        q.pop();
        if (node != nullptr)
        {
            result.emplace_back(to_string(node->val));
            q.push(node->left);
            q.push(node->right);
        }
        else
            result.emplace_back(NIL);
    }
    while (result.back() == NIL) result.pop_back();
    string str;
    for (auto &x : result)  str += (x + SEPARATOR);
    if (str.back() == SEPARATOR[0])  str.pop_back();
    return "[" + str + "]";
}
```



+ **反序列化**

还是是普通的层次遍历算法改过来的~

```cpp
TreeNode *levelDeserialize(string &data)
{
    if (data.empty())  return nullptr;
    if (data.front() == '[' && data.back() == ']')  data = data.substr(1, data.length() - 2);
    auto v = split(data, SEPARATOR);
    int idx = 0, size = v.size();
    auto root = generateNode(v[idx++]);
    assert(root != nullptr);
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {
        auto node = q.front();
        q.pop();
        if (idx < size)  node->left = generateNode(v[idx++]);
        if (idx < size)  node->right = generateNode(v[idx++]);
        if (node->left != nullptr)  q.push(node->left);
        if (node->right != nullptr) q.push(node->right);
    }
    return root;
}
```



## 前序遍历实现

利用 `stringstream` .

```cpp
class Codec {
public:
    const string nil = "#";
    const string sep = " ";
    string val;
    // Encodes a tree to a single string.
    string serialize(TreeNode* node) {
        if (node == nullptr)
            return nil;
        return to_string(node->val) + sep + serialize(node->left) + sep + serialize(node->right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream ss(data);
        return deserialize(ss);
    }

    TreeNode* generate(string &val) {
        return (val == nil || val.empty()) ? nullptr : new TreeNode(stoi(val));
    }

    TreeNode* deserialize(stringstream &ss) {
        val.clear();
        TreeNode *node = nullptr;
        if (!(ss >> val) || (node = generate(val)) == nullptr)
            return nullptr;
        node->left = deserialize(ss);
        node->right = deserialize(ss);
        return node;
    }
};
```

