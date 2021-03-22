class Solution:
    def countPrimeSetBits(self, L: int, R: int) -> int:
        primes = set({2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31})
        return len([i for i in range(L, R+1) if bin(i).count('1') in primes])
