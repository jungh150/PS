import sys
input = sys.stdin.readline

n = int(input())
a = [0] + list(map(int, input().split()))

dp = [0 for _ in range(n + 1)]
maxa = 0

for i in range(1, n + 1):
    maxt = 0
    for j in range(i):
        if a[i] > a[j]:
            maxt = max(maxt, dp[j])
    dp[i] = maxt + 1
    maxa = max(maxa, dp[i])

idx = maxa
ans = [0 for _ in range(idx + 1)]
for i in range(n, 0, -1):
    if dp[i] == idx:
        ans[idx] = a[i]
        idx -= 1

print(maxa)
for i in range(1, maxa + 1):
    print(ans[i], end = ' ')