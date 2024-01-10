from sys import stdin
from collections import deque

n, m = map(int, stdin.readline().split())
g = [[] for _ in range(n+1)]
reliable = [0] * (n+1)

def bfs(v):
    que = deque()
    que.append(v)
    visited[v] = True
    while que:
        new = que.popleft()
        for x in g[new]:
            if not visited[x]:
                que.append(x)
                visited[x] = True
                reliable[x] += 1

for _ in range(m):
    a, b = map(int, stdin.readline().split())
    g[a].append(b)

for i in range(1, n+1):
    visited = [False] * (n+1)
    bfs(i)

max = max(reliable)
for i in range(1, n+1):
    if reliable[i] == max:
        print(i, end=" ")