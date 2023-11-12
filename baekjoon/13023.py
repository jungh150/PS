from sys import stdin
import sys

sys.setrecursionlimit(10000)

n, m = map(int, stdin.readline().split())
data = [[] for i in range(n)]
visited = [False] * n

def DFS(v, depth):
    if depth == 5:
        print(1)
        exit()
    visited[v] = True
    for i in data[v]:
        if not visited[i-1]:
            DFS(i-1, depth+1)
    visited[v] = False # !

for i in range(m):
    a, b = map(int, stdin.readline().split())
    data[a-1].append(b)
    data[b-1].append(a)

for i in range(n):
    if not visited[i-1]:
        DFS(i-1, 1)

print(0)