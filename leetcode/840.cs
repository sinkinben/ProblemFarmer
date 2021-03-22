using System;
/*
    暴力试试
 */
namespace leetcode840
{
    public class Solution
    {
        public int NumMagicSquaresInside(int[][] grid)
        {
            if (grid.Length <= 2 || grid[0].Length <= 2)
                return 0;
            int rows = grid.Length;
            int cols = grid[0].Length;
            int result = 0;
            for (int i = 0; i <= rows - 3; i++)
            {
                for (int j = 0; j <= cols - 3; j++)
                {
                    if (check(grid, i, j))
                        result++;
                }
            }
            return result;
        }
        bool check(int[][] a, int i, int j)
        {
            bool[] table = new bool[10];
            int[] rowSum = { 0, 0, 0 };
            int[] colSum = { 0, 0, 0 };
            Array.Clear(table, 0, table.Length);
            int ti = i;
            int tj = j;
            for (i = ti; i < ti + 3; i++)
            {
                for (j = tj; j < tj + 3; j++)
                {
                    if (a[i][j] > 9 || table[a[i][j]])
                        return false;
                    else
                    {
                        table[a[i][j]] = true;
                        rowSum[i - ti] += a[i][j];
                        colSum[j - tj] += a[i][j];
                    }
                }
            }
            for (i = 0; i < 3; i++)
            {
                if (rowSum[i] != 15 || colSum[i] != 15)
                    return false;
            }
            if ((a[ti][tj] + a[ti + 1][tj + 1] + a[ti + 2][tj + 2]) != 15 || (a[ti][tj + 2] + a[ti + 1][tj + 1] + a[ti + 2][tj]) != 15)
                return false;
            return true;
        }
        public static void Main(string[] args)
        {
            Solution solution = new Solution();
            int[][] a = {
                new int[] {4,3,8,4},
                new int[] {9,5,1,9},
                new int[] {2,7,6,2}};
            Console.WriteLine(solution.NumMagicSquaresInside(a));
        }
    }

}