from sys import stdin
from collections import deque

n = int(stdin.readline())
m = int(stdin.readline())
g = [[] for _ in range(n+1)]
ig = [[] for _ in range(n+1)]
indegree = [0] * (n+1)
time = [0] * (n+1)
que = deque()

for _ in range(m):
    a, b, c = map(int, stdin.readline().split())
    g[a].append((b, c))
    ig[b].append((a, c))
    indegree[b] += 1

start, end = map(int, stdin.readline().split())

que.append(start)

while que:
    now = que.popleft()
    for next in g[now]:
        indegree[next[0]] -= 1
        time[next[0]] = max(time[next[0]], time[now] + next[1])
        if indegree[next[0]] == 0:
            que.append(next[0])

visited = [False] * (n+1)
cnt = 0
que.clear()
que.append(end)

while que:
    now = que.popleft()
    for next in ig[now]:
        if time[next[0]] + next[1] == time[now]:
            cnt += 1
            if not visited[next[0]]:
                que.append(next[0])
                visited[next[0]] = True

print(time[end])
print(cnt)