## Sparse Matrix Multiplication

Leetcode: [311. Sparse Matrix Multiplication](https://leetcode-cn.com/problems/sparse-matrix-multiplication/)

Given two sparse matrices `mat1` of size `m x k` and `mat2` of size `k x n`, return the result of `mat1 x mat2`. You may assume that multiplication is always possible.

**Brute Force Solution**

```cpp
class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        if (mat1.empty() || mat1[0].empty() || mat2.empty() || mat2[0].empty())
            return {};
        int m = mat1.size();
        int n = mat2[0].size();
        vector<vector<int>> res(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                res[i][j] = compute(mat1[i], mat2, j);
        return res;
    }
    int compute(vector<int> &row, vector<vector<int>> &mat2, int col)
    {
        int n = row.size(), res = 0;
        for (int i = 0; i < n; ++i)
            res += row[i] * mat2[i][col];
        return res;
    }
};
```

<br/>

**Make triples**

- For each position `(i, j)`, make a triple `(i, j, mat[i][j])`. This is what `flattern` does.
- For `(i1, j1, val1)` in `mat1`, and `(i2, j2, val2)` in `mat2`.
  - If `j1 == i2`, then we should let `res[i1][j2] += val1 * val2`.

```cpp
struct triple {
    int i, j, val;
    triple(int i, int j, int val) : i(i), j(j), val(val) {}
};
class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        if (mat1.empty() || mat1[0].empty() || mat2.empty() || mat2[0].empty())
            return {};
        auto v1 = flattern(mat1);
        auto v2 = flattern(mat2);
        vector<vector<int>> res(mat1.size(), vector<int>(mat2[0].size(), 0));
        for (auto [i1, j1, val1] : v1)
            for (auto [i2, j2, val2] : v2)
                if (j1 == i2)
                    res[i1][j2] += val1 * val2;
        return res;
    }
    
    vector<triple> flattern(vector<vector<int>> &m)
    {
        vector<triple> vec;
        int rows = m.size(), cols = m[0].size();
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                vec.emplace_back(i, j, m[i][j]);
        return vec;
    }
};
```

