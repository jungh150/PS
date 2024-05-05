import sys
input = sys.stdin.readline

mod = 1000000000

n = int(input())
dp = [[0 for _ in range(n + 1)] for _ in range(10)]

for i in range(1, 10):
    dp[i][1] = 1

for j in range(2, n + 1):
    dp[0][j] = dp[1][j - 1]
    dp[9][j] = dp[8][j - 1]
    for i in range(1, 9):
        dp[i][j] = (dp[i - 1][j - 1] + dp[i + 1][j - 1]) % mod

ans = 0
for i in range(10):
    ans = (ans + dp[i][n]) % mod

print(ans)