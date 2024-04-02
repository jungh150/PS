import sys
input = sys.stdin.readline
mod = 1000000000

n = int(input())
dp = [0 for _ in range(1000001)]

dp[2] = 1
for i in range(3, n + 1):
    dp[i] = (i - 1) * (dp[i - 2] + dp[i - 1])
    dp[i] %= mod

print(dp[n])