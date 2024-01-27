from sys import stdin

n, m, k = map(int, stdin.readline().split())
g = [[] for _ in range(n+1)]

for _ in range(m):
    s, e, w = map(int, stdin.readline().split())
    g[s].append((e, w))