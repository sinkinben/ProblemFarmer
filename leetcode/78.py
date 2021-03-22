class Solution:
    def __init__(self):
        self.ans = list()
        self.ans.append([])

    def subsets(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        cur = []
        self.helper(cur, nums)
        return self.ans

    def helper(self, cur: list, nums: list):
        for i in range(0, len(nums)):
            cur.append(nums[i])
            self.ans.append(list(cur))
            self.helper(cur, nums[(i + 1):])
            cur.pop()


s = Solution()
print(s.subsets([1, 2, 3]))
