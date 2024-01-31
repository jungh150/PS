from sys import stdin
import sys

n = int(stdin.readline())
m = int(stdin.readline())
g = [[sys.maxsize for _ in range(n+1)] for _ in range(n+1)]

for i in range(n+1):
    g[i][i] = 0

for _ in range(m):
    a, b, c = map(int, stdin.readline().split())
    if c < g[a][b]:
        g[a][b] = c

for i in range(1, n+1): # 경유지 i에 관해
    for j in range(1, n+1): # 출발 노드 j 에 관해
        for k in range(1, n+1): # 도착 노드 k에 관해
            if g[j][i] + g[i][k] < g[j][k]:
                g[j][k] = g[j][i] + g[i][k]

for i in range(1, n+1):
    for j in range(1, n+1):
        if g[i][j] == sys.maxsize:
            print(0, end=' ')
        else:
            print(g[i][j], end=' ')
    print()