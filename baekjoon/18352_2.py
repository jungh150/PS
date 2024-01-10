from sys import stdin
from collections import deque

n, m, k, x = map(int, stdin.readline().split())
g = [[] for _ in range(n+1)]
visited = [-1] * (n+1)
ans = []

def bfs(v):
    que = deque()
    que.append(v)
    visited[v] += 1
    while que:
        new = que.popleft()
        if visited[new] >= k: # 이 if문만 추가
            break
        for x in g[new]:
            if visited[x] == -1:
                que.append(x)
                visited[x] = visited[new] + 1

for _ in range(m):
    a, b = map(int, stdin.readline().split())
    g[a].append(b)

bfs(x)

for i in range(1, n+1):
    if visited[i] == k:
        ans.append(i)

if ans:
    ans.sort()
    for x in ans:
        print(x)
else:
    print(-1)