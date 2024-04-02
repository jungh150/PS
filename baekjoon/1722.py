import sys
input = sys.stdin.readline

n = int(input())
data = list(map(int, input().split()))
f = [0 for _ in range(n)]
used = [0 for _ in range(n + 1)]

f[n - 1] = 1
for i in range(1, n):
    f[n - i - 1] = f[n - i] * (i + 1)

if data[0] == 1:
    k = data[1]
    ans = [0 for _ in range(n)]
    for i in range(n - 1):
        idx = 1
        while k > f[i + 1]:
            idx += 1
            k -= f[i + 1]
        for j in range(1, n + 1):
            if used[j] == 0:
                idx -= 1
                if idx == 0:
                    ans[i] = j
                    used[j] = 1
                    break
    for j in range(1, n + 1):
        if used[j] == 0:
            ans[n - 1] = j
    for x in ans:
        print(x, end=' ')
elif data[0] == 2:
    ans = 1
    for i in range(1, n):
        cnt = 0
        for j in range(1, n + 1):
            if used[j] == 0:
                cnt += 1
                if data[i] == j:
                    used[j] = 1
                    break
        ans += (cnt - 1) * f[i]
    print(ans)