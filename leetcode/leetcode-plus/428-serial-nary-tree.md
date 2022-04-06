## Serial N-ary Tree

Leetcode: [428. Serialize and Deserialize N-ary Tree](https://leetcode-cn.com/problems/serialize-and-deserialize-n-ary-tree/)

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize an N-ary tree. An N-ary tree is a rooted tree in which each node has no more than N children. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that an N-ary tree can be serialized to a string and this string can be deserialized to the original tree structure.

For example, you may serialize the following `3-ary` tree

<img src="https://assets.leetcode.com/uploads/2018/10/12/narytreeexample.png" style="width:30%"/>

as `[1 [3[5 6] 2 4]]`. Note that this is just an example, you do not necessarily need to follow this format.

Or you can follow LeetCode's level order traversal serialization format, where each group of children is separated by the null value.

<img src="https://assets.leetcode.com/uploads/2019/11/08/sample_4_964.png" style="width:30%"/>

For example, the above tree may be serialized as `[1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]`.

You do not necessarily need to follow the above-suggested formats, there are many more different formats that work so please be creative and come up with different approaches yourself.

**Solution**

```cpp
class Codec {
public:
    const string sep = " ";
    const string nil = "";
    // Encodes a tree to a single string.
    string serialize(Node* node) {
        if (node == nullptr) return nil;
        string res = "[" + to_string(node->val);
        for (auto child : node->children)
            res += sep + serialize(child);
        return res + "]";
    }
	
    bool isdigit(char x) { return '0' <= x && x <= '9'; }

    int findLeftBracket(const string &str, int idx)
    {
        int n = str.length();
        while (idx < n && str[idx] != '[')
            idx++;
        return idx;
    }
    
    int findRightBracket(const string &str, int idx)
    {
        int n = str.length(), cnt = 0;
        do
        {
            cnt += str[idx] == '[';
            cnt -= str[idx] == ']';
            idx++;
            assert(cnt >= 0);
        } while (cnt != 0);
        return idx - 1;
    }
    
    // Decodes your encoded data to tree.
    Node* deserialize(const string &str) {
        if (str.empty()) return nullptr;
        
        assert(str.length() > 2 && str[0] == '[' && str.back() == ']');
        int n = str.length(), i = 1, val = 0;
        while (i < n - 1 && isdigit(str[i]))
            val = val * 10 + (str[i++] - '0');
        Node *root = new Node(val);
        
        while (i < n - 1)
        {
            int l = findLeftBracket(str, i);
            int r = findRightBracket(str, l);
            root->children.emplace_back(deserialize(str.substr(l, r - l + 1)));
            i = r + 1;
        }
        return root;
    }
};
```

