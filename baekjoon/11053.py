import sys
input = sys.stdin.readline

n = int(input())
a = list(map(int, input().split()))

dp = [0 for _ in range(n)]
maxa = 0

for i in range(n):
    maxt = 0
    for j in range(i):
        if a[i] > a[j]:
            maxt = max(maxt, dp[j])
    dp[i] = maxt + 1
    maxa = max(maxa, dp[i])

print(maxa)