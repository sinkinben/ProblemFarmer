## Sentence Screen Fitting

Leetcode: https://leetcode-cn.com/problems/sentence-screen-fitting/

Given a `rows x cols` screen and a sentence represented by a list of **non-empty** words, find **how many times** the given sentence can be fitted on the screen.

**Note:**

1. A word cannot be split into two lines.
2. The order of words in the sentence must remain unchanged.
3. Two consecutive words in a line **must be** separated by a single space.
4. Total words in the sentence won't exceed 100.
5. Length of each word is greater than 0 and won't exceed 10.
6. `1 <= rows, cols <= 20,000`.

**Example 1:**

```
Input:
rows = 2, cols = 8, sentence = ["hello", "world"]

Output: 
1

Explanation:
hello---
world---

The character '-' signifies an empty space on the screen.
```

**Example 2:**

```
Input:
rows = 3, cols = 6, sentence = ["a", "bcd", "e"]

Output: 
2

Explanation:
a-bcd- 
e-a---
bcd-e-

The character '-' signifies an empty space on the screen.
```

**Example 3:**

```
Input:
rows = 4, cols = 5, sentence = ["I", "had", "apple", "pie"]

Output: 
1

Explanation:
I-had
apple
pie-I
had--

The character '-' signifies an empty space on the screen.
```



## Brute Force (TLE)

Print a word each time, let `(i, j)` denote the position we can print at the next time.

```cpp
class Solution
{
public:
    int wordsTyping(vector<string> &sentence, int rows, int cols)
    {
        int size = sentence.size();
        vector<int> lens(size, 0);
        
        for (int k = 0; k < size; ++k) lens[k] = sentence[k].length();

        int i = 0, j = 0, ptr = 0, res = 0;
        while (i < rows && j < cols)
        {
            bool needSpace = true;
            if (j + lens[ptr] <= cols)
            {
                j += lens[ptr++];
                if (j >= cols) i += 1, j = 0, needSpace = false;
            }
            else
            {
                if (i == rows - 1) break;
                i += 1, j = 0;
                // if a row can not put a single word in
                if (lens[ptr] > cols) return 0;
                j += lens[ptr++];
            }
            if (needSpace && (++j) >= cols) i += 1, j = 0;
            if (ptr >= size) ptr = 0, res += 1;
            
        }
        return res;
    }
};
```



## Optimization (Accepted)

```cpp
class Solution
{
public:
    bool isLetter(char x) { return x != ' '; }
    int wordsTyping(vector<string> &sentence, int rows, int cols)
    {
        string str;
        for (auto &x : sentence) str += x + " ";
        
        // pos points to the start-position that we can print in the `str`
        int len = str.length(), pos = 0;
        for (int i = 0; i < rows; ++i)
        {
            pos += cols;
            // there should be a space after a word, `pos + 1` should be a char
            if (str[pos % len] == ' ') pos++;
            else
            {
                /* The remained parts of a row, can not fit a total word.
                 * For current word, we need to find its start-position.
                 */
                while (pos > 0 && isLetter(str[pos % len])) pos--;
                pos++;
            }
        }
        return pos / len;
    }
};
```

