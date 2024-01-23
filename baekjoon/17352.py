from sys import stdin
import sys
sys.setrecursionlimit(100000)

def find(a):
    if parent[a] == a:
        return a
    else:
        parent[a] = find(parent[a])
        return parent[a]

def union(a, b):
    a = find(a)
    b = find(b)
    if a != b:
        parent[b] = a

n = int(stdin.readline())
parent = [i for i in range(n+1)]

for _ in range(n-2):
    a, b = map(int, stdin.readline().split())
    union(a, b)

x = find(1)
for i in range(2, n+1):
    if find(i) != x:
        print(x, i)
        break