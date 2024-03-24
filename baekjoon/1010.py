from sys import stdin

dp = [[0 for _ in range(30)] for _ in range(30)]

dp[0][0] = 1

for i in range(1, 30):
    dp[i][0] = dp[i][i] = 1
    for j in range(1, i):
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]

t = int(stdin.readline())
for _ in range(t):
    n, m = map(int, stdin.readline().split())
    print(dp[m][n])