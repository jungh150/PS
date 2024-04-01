from sys import stdin

r, c, w = map(int, stdin.readline().split())
dp = [[0 for _ in range(31)] for _ in range(31)]

dp[0][0] = 1

for i in range(1, r + w + 1):
    dp[i][0] = 1
    dp[i][i] = 1
    for j in range(1, i):
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]

sum = 0

for i in range(w):
    x = r + i - 1
    for y in range(c - 1, c + i):
        sum += dp[x][y]

print(sum)