from sys import stdin
from collections import deque

n, m = map(int, stdin.readline().split())
g = [[] for _ in range(n+1)]
hacking = [0] * (n+1)

def bfs(v):
    cnt = 0
    que = deque()
    visited = [False] * (n+1)
    que.append(v)
    visited[v] = True
    while que:
        new = que.popleft()
        for x in g[new]:
            if not visited[x]:
                que.append(x)
                visited[x] = True
                cnt += 1
    return cnt

for _ in range(m):
    a, b = map(int, stdin.readline().split())
    g[b].append(a)

for i in range(1, n+1):
    hacking[i] = bfs(i)

max = max(hacking)
for i in range(1, n+1):
    if hacking[i] == max:
        print(i, end=" ")