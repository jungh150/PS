from sys import stdin
import sys
import heapq

n, m, k = map(int, stdin.readline().split())
g = [[] for _ in range(n+1)]
dst = [[sys.maxsize] * k for _ in range(n+1)]

for _ in range(m):
    s, e, w = map(int, stdin.readline().split())
    g[s].append((e, w))

que = [(0, 1)]
dst[1][0] = 0

while que:
    cost, node = heapq.heappop(que)
    for nnode, ncost in g[node]:
        c = cost + ncost
        if dst[nnode][k-1] > c: # 아직 k번째 최단경로를 못 찾았다면
            dst[nnode][k-1] = c
            dst[nnode].sort()
            heapq.heappush(que, (c, nnode))

for i in range(1, n+1):
    if dst[i][k-1] == sys.maxsize:
        print(-1)
    else:
        print(dst[i][k-1])