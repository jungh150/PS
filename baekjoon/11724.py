from sys import stdin
import sys

sys.setrecursionlimit(10000)

n, m = map(int, stdin.readline().split())
data = [[] for i in range(n)]
visited = [False] * n

def DFS(v):
    visited[v] = True
    for i in data[v]:
        if not visited[i-1]:
            DFS(i-1)

for i in range(m):
    a, b = map(int, stdin.readline().split())
    data[a-1].append(b)
    data[b-1].append(a)

count = 0

for i in range(n):
    if not visited[i-1]:
        DFS(i-1)
        count += 1

print(count)