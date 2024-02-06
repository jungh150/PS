from sys import stdin
import sys

n, m = map(int, stdin.readline().split())
g = [[sys.maxsize for _ in range(n+1)] for _ in range(n+1)]
ans = []

for i in range(1, n+1):
    g[i][i] = 0

for _ in range(m):
    a, b = map(int, stdin.readline().split())
    g[a][b] = 1
    g[b][a] = 1

for i in range(1, n+1): # 경유지 i에 대해
    for j in range(1, n+1): # 출발 노드 j에 대해
        for k in range(1, n+1): # 도착 노드 k에 대해
            if g[j][i] + g[i][k] < g[j][k]:
                g[j][k] = g[j][i] + g[i][k]

for i in range(1, n+1):
    for j in range(1, n+1):
        if j == i:
            continue
        tmp = 0
        for k in range(1, n+1):
            tmp += min(g[k][i], g[k][j])
        ans.append((tmp, i, j))

ans.sort()

print(ans[0][1], ans[0][2], ans[0][0] * 2)