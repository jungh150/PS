import sys
input = sys.stdin.readline

n = int(input())
data = [0 for _ in range(n + 1)]
dp = [0 for _ in range(n + 1)]

for i in range(1, n + 1):
    data[i] = int(input())

# 점화식 dp[n] = max(dp[n - 1], dp[n - 2] + data[n],
#                   dp[n - 3] + data[n - 1] + data[n])

dp[1] = data[1]

if n > 1:
    dp[2] = data[1] + data[2]
    
for i in range(3, n + 1):
    dp[i] = max(dp[i - 1], dp[i - 2] + data[i],
                dp[i - 3] + data[i - 1] + data[i])

print(dp[n])