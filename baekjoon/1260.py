from sys import stdin
from collections import deque

n, m, s = map(int, stdin.readline().split())
data = [[] for i in range(n)]
visited = [False] * n

for i in range(m):
    a, b = map(int, stdin.readline().split())
    data[a-1].append(b)
    data[b-1].append(a)

for i in range(n):
    data[i].sort()

def DFS(v):
    visited[v] = True
    print(v+1, end=" ")
    for i in data[v]:
        if not visited[i-1]:
            DFS(i-1)

def BFS(v):
    que = deque()
    visited[v] = True
    que.append(v+1)
    while que:
        v = que.popleft()
        print(v, end=" ")
        for i in data[v-1]:
            if not visited[i-1]:
                visited[i-1] = True
                que.append(i)

DFS(s-1)

print()
visited = [False] * n

BFS(s-1)