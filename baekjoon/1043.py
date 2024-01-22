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
true = list(map(int, stdin.readline().split()))
party = []
for _ in range(m):
    party.append(list(map(int, stdin.readline().split())))
parent = [i for i in range(n+1)]
ans = 0

for i in range(m):
    for j in range(2, party[i][0]+1):
        union(party[i][1], party[i][j])

for i in range(m):
    possible = True
    for j in range(1, true[0]+1):
        if find(party[i][1]) == find(true[j]):
            possible = False
            break
    if possible:
        ans += 1
    
print(ans)