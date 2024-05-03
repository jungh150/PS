import sys
input = sys.stdin.readline
m = 10007

n = int(input())
# dp: 순열
dp = [[0 for _ in range(n + 1)] for _ in range(n + 1)]

dp[0][0] = 1
for i in range(1, n + 1):
    dp[i][0] = dp[i][i] = 1
    for j in range(1, i):
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]

ans = 0
i = n
j = 0
while i >= j:
    ans = (ans + dp[i][j]) % m
    i -= 1
    j += 1

print(ans) 