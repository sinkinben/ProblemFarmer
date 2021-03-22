using System;
using System.Collections.Generic;
namespace leetcode637
{
    public class TreeNode
    {
        public int val;
        public TreeNode left, right;
        public TreeNode(int x) { val = x; }
    }
    public class Solution
    {
        public IList<double> AverageOfLevels(TreeNode root)
        {
            return level(root);
        }

        public IList<double> level(TreeNode root)
        {
            Queue<int> q1 = new Queue<int>();
            Queue<TreeNode> q2 = new Queue<TreeNode>();
            Dictionary<int, Int64> d1 = new Dictionary<int, Int64>();
            Dictionary<int, int> d2 = new Dictionary<int, int>();
            q1.Enqueue(1);
            q2.Enqueue(root);
            while (q1.Count != 0 && q2.Count != 0)
            {
                TreeNode node = q2.Dequeue();
                int l = q1.Dequeue();
                if (d1.ContainsKey(l))
                {
                    d1[l] += node.val;
                }
                else
                {
                    d1.Add(l, node.val);
                }
                if (d2.ContainsKey(l))
                {
                    d2[l]++;
                }
                else
                {
                    d2.Add(l, 1);
                }
                if (node.left != null)
                {
                    q1.Enqueue(l + 1);
                    q2.Enqueue(node.left);
                }
                if (node.right != null)
                {
                    q1.Enqueue(l + 1);
                    q2.Enqueue(node.right);
                }
            }
            List<double> list = new List<double>();
            foreach (KeyValuePair<int, Int64> kv in d1)
            {
                list.Add((double)(kv.Value) / (d2[kv.Key]));
            }
            return list;
        }
    }
}