import sys
input = sys.stdin.readline
m = 10007

n = int(input())
dp = [0 for _ in range(n + 1)]

# 점화식 dp[n] = dp[n-1] + dp[n-2]

dp[1] = 1
if n > 1:
    dp[2] = 2

for i in range(3, n + 1):
    dp[i] = (dp[i - 1] + dp[i - 2]) % m

print(dp[n])