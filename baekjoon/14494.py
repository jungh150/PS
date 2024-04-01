from sys import stdin

# 점화식 : dp[i][j] = dp[i-1][j] + dp[i][j-1] + dp[i-1][j-1]

mod = 1000000007
n, m = map(int, stdin.readline().split()) # n 가로 m 세로
dp = [[0 for _ in range(n + 1)] for _ in range (m + 1)]

for i in range(1, n + 1):
    dp[1][i] = 1

for i in range(2, m + 1):
    dp[i][1] = 1
    for j in range(2, n + 1):
        dp[i][j] = (dp[i-1][j] + dp[i][j-1] + dp[i-1][j-1]) % mod

print(dp[m][n])