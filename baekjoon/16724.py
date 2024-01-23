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

n, m = map(int, stdin.readline().split())
parent = [i for i in range(n*m + 1)]

for i in range(n):
    input = stdin.readline()
    for j in range(m):
        if input[j] == 'U':
            union(i*m + (j+1), (i-1)*m + (j+1))
        elif input[j] == 'D':
            union(i*m + (j+1), (i+1)*m + (j+1))
        elif input[j] == 'L':
            union(i*m + (j+1), i*m + j)
        elif input[j] == 'R':
            union(i*m + (j+1), i*m + (j+2))

ans = []
for i in range(1, n*m + 1):
    ans.append(find(i))
print(len(set(ans)))