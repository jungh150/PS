import sys
input = sys.stdin.readline

n, m, k = map(int, input().split())
dp = [[0 for _ in range(n + m - 1)] for _ in range(n + m - 1)]
ans = 0

dp[0][0] = 1
for i in range(1, n + m - 1):
    dp[i][0] = dp[i][i] = 1
    for j in range(1, i):
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]

if k == 0:
    ans = dp[n + m - 2][n - 1]
else:
    r = k // m + 1
    c = k % m
    ans = dp[r + c - 2][r - 1] * dp[n - r + m - c][n - r]

print(ans)

# 이렇게 하면 벽에 동그라미가 벽에 인접하면 곱해서 0이 나옴