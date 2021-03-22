using System;
namespace leetcode1138
{
    public class Solution
    {
        public string AlphabetBoardPath(string target)
        {
            char now = 'a';
            int ni = 0, nj = 0;
            int ti, tj;
            string result = "";
            foreach (char x in target)
            {
                ni = getRowIndex(now);
                nj = getColIndex(now);
                ti = getRowIndex(x);
                tj = getColIndex(x);
                if (ni == ti && nj == tj)
                {
                    result += "!";
                    now = x;
                    continue;
                }
                if (now == 'z')
                {
                    UDMove(ni, ti, ref result, ref target);
                    LRMove(nj, tj, ref result, ref target);
                }
                else
                {
                    LRMove(nj, tj, ref result, ref target);
                    UDMove(ni, ti, ref result, ref target);
                }
                now = x;
                result += "!";
            }
            return result;
        }

        int getRowIndex(char c)
        {
            int k = c - 'a';
            return k / 5;
        }
        int getColIndex(int c)
        {
            int k = c - 'a';
            return k % 5;
        }

        void LRMove(int nj, int tj, ref string result, ref string target)
        {
            if (nj < tj)
            {
                while (nj < tj)
                {
                    result += "R";
                    nj++;
                }
            }
            else if (nj > tj)
            {
                while (nj > tj)
                {
                    result += "L";
                    nj--;
                }
            }
        }
        void UDMove(int ni, int ti, ref string result, ref string target)
        {
            if (ni < ti)
            {
                while (ni < ti)
                {
                    result += "D";
                    ni++;
                }
            }
            else if (ni > ti)
            {
                while (ni > ti)
                {
                    result += "U";
                    ni--;
                }
            }
        }

        public static void Main(string[] args)
        {
            Solution solution = new Solution();
            Console.WriteLine(solution.AlphabetBoardPath("zdz"));
        }
    }
}