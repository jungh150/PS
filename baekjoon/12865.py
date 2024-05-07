import sys
input = sys.stdin.readline

n, k = map(int, input().split())
dp = [[0 for _ in range(n + 1)] for _ in range(k + 1)]
w = [0] * (n + 1)
v = [0] * (n + 1)

for i in range(1, n + 1):
    w[i], v[i] = map(int, input().split())

for i in range(1, k + 1):
    for j in range(1, n + 1):
        if w[j] <= i:
            dp[i][j] = max(dp[i][j - 1], dp[i - w[j]][j - 1] + v[j])
        else:
            dp[i][j] = dp[i][j - 1]

print(dp)
print(dp[k][n])