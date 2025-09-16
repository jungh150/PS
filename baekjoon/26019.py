import sys
input = sys.stdin.readline

MAX_VAL = 10 ** 18

n, m = map(int, input().split())

a = [[] for _ in range(n + 1)]
for i in range(1, n + 1):
    a[i] = list(map(int, input().split()))

dp = [MAX_VAL for _ in range(n + 2)] # min total cost (i ~ n month)
dp[n + 1] = 0

for i in range(n, 0, -1):
    k = min(m, n - i + 1)
    for j in range(1, k + 1):
        dp[i] = min(dp[i], a[i][0] - a[i][j] + dp[i + j])

print(dp[1])