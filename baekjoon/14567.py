from sys import stdin
from collections import deque

n, m = map(int, stdin.readline().split())
g = [[] for _ in range(n+1)]
indegree = [0] * (n+1)
time = [0] * (n+1)
que = deque()

for _ in range(m):
    a, b = map(int, stdin.readline().split())
    g[a].append(b)
    indegree[b] += 1

for i in range(1, n+1):
    if indegree[i] == 0:
        que.append(i)
        time[i] += 1

while que:
    now = que.popleft()
    for next in g[now]:
        time[next] = time[now] + 1
        indegree[next] -= 1
        if indegree[next] == 0:
            que.append(next)

for i in range(1, n+1):
    print(time[i], end=' ')