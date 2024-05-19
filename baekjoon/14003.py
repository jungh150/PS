import sys
input = sys.stdin.readline

n = int(input())
a = [0] + list(map(int, input().split()))

dp = [0 for _ in range(n + 1)]
b = [0 for _ in range(n + 1)]
idx = 0
maxl = 1
b[1] = a[1]
dp[1] = 1

def binarysearch(l, r, now):
    while l < r:
        mid = (l + r) // 2
        if b[mid] < now:
            l = mid + 1
        else:
            r = mid
    return l

for i in range(2, n + 1):
    if b[maxl] < a[i]:
        maxl += 1
        b[maxl] = a[i]
        dp[i] = maxl
    else:
        idx = binarysearch(1, maxl, a[i])
        b[idx] = a[i]
        dp[i] = idx

idx = maxl
ans = [0 for _ in range(idx + 1)]
for i in range(n, 0, -1):
    if dp[i] == idx:
        ans[idx] = a[i]
        idx -= 1

print(maxl)
for i in range(1, maxl + 1):
    print(ans[i], end = ' ')