import sys
from collections import deque
input = sys.stdin.readline

n = int(input())
tree = [[] for _ in range(n+1)]
depth = [0] * (n+1)
parent = [0] * (n+1)
visited = [False] * (n+1)

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
                parent[nxt] = now
                depth[nxt] = level
        cnt += 1
        if cnt == size:
            cnt = 0
            size = len(que)
            level += 1

def LCA(a, b):
    if depth[a] < depth[b]:
        tmp = a
        a = b
        b = tmp
    
    while depth[a] != depth[b]:
        a = parent[a]
    
    while a != b:
        a = parent[a]
        b = parent[b]
    
    return a

for _ in range(n-1):
    a, b = map(int, input().split())
    tree[a].append(b)
    tree[b].append(a)

bfs(1)

m = int(input())
for _ in range(m):
    a, b = map(int, input().split())
    print(LCA(a, b))