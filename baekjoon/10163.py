import sys
input = sys.stdin.readline

a = [[0 for _ in range(1001)] for _ in range(1001)]

n = int(input())

for x in range(1, n + 1):
    c, r, w, h = map(int, input().split())
    for i in range(r, r + h):
        for j in range(c, c + w):
            a[i][j] = x

ans = [0 for _ in range(n + 1)]

for i in range(1001):
    for j in range(1001):
        ans[a[i][j]] += 1

for x in range(1, n + 1):
    print(ans[x])