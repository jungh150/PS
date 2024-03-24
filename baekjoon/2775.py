from sys import stdin

dp = [[0 for _ in range(15)] for _ in range(15)]

for i in range(1, 15):
    dp[0][i] = i

for i in range(1, 15):
    dp[i][1] = dp[i - 1][1]
    for j in range(2, 15):
        dp[i][j] = dp[i][j - 1] + dp[i - 1][j]

t = int(stdin.readline())
for _ in range(t):
    k = int(stdin.readline())
    n = int(stdin.readline())
    print(dp[k][n])