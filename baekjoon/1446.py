from sys import stdin
import sys
from queue import PriorityQueue

n, d = map(int, stdin.readline().split())
g = [[] for _ in range(10001)]
visited = [False] * (10001)
dst = [sys.maxsize] * (10001)
que = PriorityQueue()

for i in range(d):
    g[i].append((i+1, 1))

for _ in range(n):
    a, b, c = map(int, stdin.readline().split())
    g[a].append((b, c))

dst[0] = 0
que.put((0, 0))

while que.qsize() > 0:
    now = que.get()
    if visited[now[1]]:
        continue
    visited[now[1]] = True
    for next in g[now[1]]:
        if dst[now[1]] + next[1] < dst[next[0]]:
            dst[next[0]] = dst[now[1]] + next[1]
            que.put((dst[next[0]], next[0]))

print(dst[d])