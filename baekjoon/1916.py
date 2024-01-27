from sys import stdin
import sys
from queue import PriorityQueue

n = int(stdin.readline())
m = int(stdin.readline())
g = [[] for _ in range(n+1)]
dst = [sys.maxsize] * (n+1)
visited = [False] * (n+1)
que = PriorityQueue()

for _ in range(m):
    s, e, w = map(int, stdin.readline().split())
    g[s].append((e, w))

start, end = map(int, stdin.readline().split())
dst[start] = 0
que.put((0, start))

while que.qsize() > 0:
    now = que.get()
    if visited[now[1]]:
        continue
    visited[now[1]] = True
    for next in g[now[1]]:
        if dst[now[1]] + next[1] < dst[next[0]]:
            dst[next[0]] = dst[now[1]] + next[1]
            que.put((dst[next[0]], next[0]))

print(dst[end])