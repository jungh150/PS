import sys
import math
from collections import deque
input = sys.stdin.readline

n = int(input())
tree = [[] for _ in range(n+1)]
depth = [0] * (n+1)
visited = [False] * (n+1)
kmax = math.floor(math.log2(n)) + 1

parent = [[0 for j in range(n+1)] for i in range(kmax+1)]

def bfs(node):
    que = deque()
    que.append(node)
    visited[node] = True
    level = 1
    size = 1
    cnt = 0
    while que:
        now = que.popleft()
        for nxt in tree[now]:
            if not visited[nxt]:
                visited[nxt] = True
                que.append(nxt)
                parent[0][nxt] = now
                depth[nxt] = level
        cnt += 1
        if cnt == size:
            cnt = 0
            size = len(que)
            level += 1

def LCA(a, b):
    if depth[a] > depth[b]:
        tmp = a
        a = b
        b = tmp
    
    for k in range(kmax, -1, -1):
        if pow(2, k) <= depth[b] - depth[a]:
            if depth[a] <= depth[parent[k][b]]:
                b = parent[k][b]
    
    for k in range(kmax, -1, -1):
        if a == b:
            break
        if parent[k][a] != parent[k][b]:
            a = parent[k][a]
            b = parent[k][b]

    res = a
    if a != b:
        res = parent[0][res]
    return res

for _ in range(n-1):
    a, b = map(int, input().split())
    tree[a].append(b)
    tree[b].append(a)

bfs(1)

for k in range(1, kmax+1):
    for n in range(1, n+1):
        parent[k][n] = parent[k-1][parent[k-1][n]]

m = int(input())
for _ in range(m):
    a, b = map(int, input().split())
    print(LCA(a, b))