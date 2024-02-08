from sys import stdin
import sys
sys.setrecursionlimit(10 ** 6)

n = int(stdin.readline())
g = [[] for _ in range(n+1)]
parent = [0] * (n+1)

def dfs(pre, cur):
    for nxt in g[cur]:
        if nxt != pre:
            parent[nxt] = cur
            dfs(cur, nxt)

for _ in range(n-1):
    a, b = map(int, stdin.readline().split())
    g[a].append(b)
    g[b].append(a)

dfs(0, 1)

for i in range(2, n+1):
    print(parent[i])