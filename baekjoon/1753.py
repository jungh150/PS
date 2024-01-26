from sys import stdin
from queue import PriorityQueue
import sys

v, e = map(int, stdin.readline().split())
g = [[] for _ in range(v+1)]
dst = [sys.maxsize] * (v+1)
visited = [False] * (v+1)
que = PriorityQueue()

start = int(stdin.readline())
dst[start] = 0
que.put((0, start))

for _ in range(e):
    a, b, c = map(int, stdin.readline().split())
    g[a].append((b, c))

while que.qsize() > 0:
    now = que.get()
    if visited[now[1]]:
        continue
    visited[now[1]] = True
    for next in g[now[1]]:
        if dst[now[1]] + next[1] < dst[next[0]]:
            dst[next[0]] = dst[now[1]] + next[1]
        que.put((dst[next[0]], next[0]))

for i in range(1, v+1):
    if visited[i]:
        print(dst[i])
    else:
        print("INF")