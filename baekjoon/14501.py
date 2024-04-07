import sys
input = sys.stdin.readline

n = int(input())
data = [[0, 0] for _ in range(n + 1)]
dp = [0 for _ in range(n + 2)]

for i in range(1, n + 1):
    a, b = map(int, input().split())
    data[i][0] = a
    data[i][1] = b

for i in range(n, 0, -1):
    if (i + data[i][0] - 1) <= n:
        dp[i] = max(data[i][1] + dp[i + data[i][0]], dp[i + 1])
    else:
        dp[i] = dp[i + 1]
    
print(dp[1])