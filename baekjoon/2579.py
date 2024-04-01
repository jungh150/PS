from sys import stdin

n = int(stdin.readline())
step = []
dp = [0 for _ in range(n)]

for _ in range(n):
    step.append(int(stdin.readline()))

dp[0] = step[0]
dp[1] = dp[0] + step[1]
dp[2] = max()

for i in range(3, n):
    dp[i] = dp[i - 3] + max(step[i - 2], step[i - 1]) + step[i]

print(dp)