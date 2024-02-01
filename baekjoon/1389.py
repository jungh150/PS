from sys import stdin
import sys

n, m = map(int, stdin.readline().split())
g = [[sys.maxsize for _ in range(n+1)] for _ in range(n+1)]

for i in range(1, n+1):
    g[i][i] = 0

for _ in range(m):
    a, b = map(int, stdin.readline().split())
    g[a][b] = 1
    g[b][a] = 1

for i in range(1, n+1):
    for j in range(1, n+1):
        for k in range(1, n+1):
            if g[j][i] + g[i][k] < g[j][k]:
                g[j][k] = g[j][i] + g[i][k]

ans = 1
min = sum(g[1])
for i in range(2, n+1):
    if sum(g[i]) < min:
        min = sum(g[i])
        ans = i

print(ans)