import sys
input = sys.stdin.readline

n, m = map(int, input().split())
dp = []
maxS = 0

for i in range(n):
    dp.append(list(map(int, list(input().strip()))))
    for j in range(m):
        if dp[i][j] == 1 and i > 0 and j > 0:
            dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]) + 1
        if maxS < dp[i][j]:
            maxS = dp[i][j]

print(maxS * maxS)