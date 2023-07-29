#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include <stack>
#include <set>
using namespace std;

// Calcute running time
#define CLOCK_START(start) (start = clock())
#define GET_DURATION(start) (1.0 * (clock() - start) / CLOCKS_PER_SEC)

template<class T>
void print(vector<T> &vec)
{
    for (T &x : vec)
        cout << x << ' ';
    cout << '\n';
}
