from sys import stdin
from collections import deque

n = int(stdin.readline())
g = [[] for _ in range(n+1)]
time = [0] * (n+1)
totalTime = [0] * (n+1)
indegree = [0] * (n+1)
que = deque()

for i in range(1, n+1):
    data = list(map(int, stdin.readline().split()))
    time[i] = data[0]
    for j in range(1, len(data)-1):
        g[data[j]].append(i)
        indegree[i] += 1

for i in range(1, n+1):
    if indegree[i] == 0:
        que.append(i)
        totalTime[i] = time[i]

while que:
    new = que.popleft()
    for x in g[new]:
        indegree[x] -= 1
        if indegree[x] == 0:
            que.append(x)
        totalTime[x] = max(totalTime[x], totalTime[new] + time[x])

for i in range(1, n+1):
    print(totalTime[i])