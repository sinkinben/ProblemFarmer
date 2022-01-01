#include "../leetcode.h"
#include <unordered_set>
#include <unordered_map>
#include <functional>
/**
 *    要保留的信息：
 *    parent -> [children ...] 大小关系
 *    children -> parent
 *    death list: [...]
 **/
class ThroneInheritance
{
public:
    int order = 0;
    unordered_map<string, int> getOrder;
    unordered_map<int, string> getName;

    // unordered_map<int, int> getParent;
    unordered_map<int, vector<int>> graph;
    unordered_set<int> deathSet;

    ThroneInheritance(string kingName)
    {
        getOrder[kingName] = order;
        getName[order] = kingName;
        graph[order] = vector<int>();
        deathSet.clear();
        order++;
    }

    void dfs(int x, vector<string> &list)
    {
        if (deathSet.count(x) == 0)
            list.push_back(getName[x]);
        for (int y : graph[x])
            dfs(y, list);
    }

    void birth(string parentName, string childName)
    {
        getOrder[childName] = order;
        getName[order] = childName;
        graph[getOrder[parentName]].push_back(order);
        order++;
    }

    void death(string name)
    {
        deathSet.insert(getOrder[name]);
    }

    vector<string> getInheritanceOrder()
    {
        vector<string> list;
        dfs(0, list);
        return list;
    }
};

/**
 * Your ThroneInheritance object will be instantiated and called as such:
 * ThroneInheritance* obj = new ThroneInheritance(kingName);
 * obj->birth(parentName,childName);
 * obj->death(name);
 * vector<string> param_3 = obj->getInheritanceOrder();
 */
int main()
{
    ThroneInheritance t("king");  // 继承顺序：king
    t.birth("king", "andy");      // 继承顺序：king > andy
    t.birth("king", "bob");       // 继承顺序：king > andy > bob
    t.birth("king", "catherine"); // 继承顺序：king > andy > bob > catherine
    t.birth("andy", "matthew");   // 继承顺序：king > andy > matthew > bob > catherine
    t.birth("bob", "alex");       // 继承顺序：king > andy > matthew > bob > alex > catherine
    t.birth("bob", "asha");       // 继承顺序：king > andy > matthew > bob > alex > asha > catherine
    // cout << "here" << endl;
    t.getInheritanceOrder(); // 返回 ["king", "andy", "matthew", "bob", "alex", "asha", "catherine"]
    // cout << "here" << endl;
    t.death("bob");          // 继承顺序：king > andy > matthew > bob（已经去世）> alex > asha > catherine
    t.getInheritanceOrder(); // 返回 ["king", "andy", "matthew", "alex", "asha", "catherine"]
}