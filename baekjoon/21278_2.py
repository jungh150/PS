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

for i in range(1, n+1): # 경유지 i에 대해
    for j in range(1, n+1): # 출발 노드 j에 대해
        for k in range(1, n+1): # 도착 노드 k에 대해
            if g[j][i] + g[i][k] < g[j][k]:
                g[j][k] = g[j][i] + g[i][k]

ch1 = 1
ch2 = 1
acc = sys.maxsize

for i in range(1, n+1):
    for j in range(i+1, n+1):
        tmp = 0
        for k in range(1, n+1):
            tmp += min(g[k][i], g[k][j])
        if tmp < acc:
            ch1 = i
            ch2 = j
            acc = tmp

print(ch1, ch2, acc * 2)