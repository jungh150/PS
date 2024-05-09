import sys
input = sys.stdin.readline

n = int(input())
step = [0 for _ in range(n + 1)]
dp = [0 for _ in range(n + 1)]

for i in range(1, n + 1):
    step[i] = int(input())

dp[1] = step[1]

if n >= 2:
    dp[2] = dp[1] + step[2]

for i in range(3, n + 1):
    dp[i] = max(dp[i - 2], dp[i - 3] + step[i - 1]) + step[i]

print(dp[n])