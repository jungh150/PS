from sys import stdin
import sys

sys.setrecursionlimit(10**6)

def dfs(v):
    check = True
    visited[v] = True
    for x in g[v]:
        if not visited[x]:
            set[x] = (set[v] + 1) % 2
            dfs(x)
        else:
            if set[x] == set[v]:
                check = False
                break
    return check

k = int(stdin.readline())
for _ in range(k):
    v, e = map(int, stdin.readline().split())
    g = [[] for _ in range(v+1)]
    visited = [False] * (v+1)
    set = [0] * (v+1)

    for _ in range(e):
        a, b = map(int, stdin.readline().split())
        g[a].append(b)
        g[b].append(a)

    isBip = True
    for i in range(v+1):
        if not dfs(i):
            isBip = False
            break
    
    if isBip:
        print("YES")
    else:
        print("NO")