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

n = int(stdin.readline())
m = int(stdin.readline())
city = []
parent = [i for i in range(n+1)]
possible = True

for _ in range(n):
    city.append(list(map(int, stdin.readline().split())))

plan = list(map(int, stdin.readline().split()))

for i in range(n):
    for j in range(n):
        if city[i][j] == 1:
            union(i+1, j+1)

for i in range(1, m):
    if find(plan[0]) != find(plan[i]):
        possible = False
        break

if possible:
    print("YES")
else:
    print("NO")