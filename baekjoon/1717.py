from sys import stdin

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

n, m = map(int, stdin.readline().split())
parent = [i for i in range(n+1)]

for _ in range(m):
    x, a, b = map(int, stdin.readline().split())
    if x == 0:
        union(a, b)
    elif x == 1:
        if find(a) == find(b):
            print("YES")
        else:
            print("NO")