from sys import stdin
from collections import deque

n, m = map(int, stdin.readline().split())
g = [[] for _ in range(n+1)]
indegree = [0] * (n+1)
que = deque()

for _ in range(m):
    a, b = map(int, stdin.readline().split())
    g[a].append(b)
    indegree[b] += 1

for i in range(1, n+1):
    if indegree[i] == 0:
        que.append(i)

while que:
    new = que.popleft()
    print(new, end=' ')
    for x in g[new]:
        indegree[x] -= 1
        if indegree[x] == 0:
            que.append(x)