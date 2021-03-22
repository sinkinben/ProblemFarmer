using System;
using System.Collections.Generic;
namespace leetcode905
{
    public class Solution
    {
        public int[] SortArrayByParity(int[] A)
        {
            LinkedList<int> list = new LinkedList<int>();
            foreach (int x in A)
            {
                if (x % 2 == 0)
                    list.AddFirst(x);
                else
                    list.AddLast(x);
            }
            int[] result = new int[list.Count];
            int i = 0;
            foreach (int x in list)
            {
                result[i++] = x;
            }
            return result;
        }
        public static void Main(string[] args)
        {
            Solution solution = new Solution();
            int[] a = { 1, 2, 3, 4 };
            foreach (int x in solution.SortArrayByParity(a))
            {
                Console.Write(x + " ");
            }
        }
    }
}