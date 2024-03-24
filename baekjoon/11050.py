from sys import stdin

n, k = map(int, stdin.readline().split())
dp = [[0 for _ in range(n + 1)] for _ in range(n + 1)]

dp[0][0] = 1

for i in range(1, n + 1):
    dp[i][0] = dp[i][i] = 1
    for j in range(1, i):
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]

print(dp[n][k])