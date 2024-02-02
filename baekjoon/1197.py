from sys import stdin

v, e = map(int, stdin.readline().split())
edge = []
parent = [i for i in range(v+1)]

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

for _ in range(e):
    a, b, c = map(int, stdin.readline().split())
    edge.append((a, b, c))

edge.sort(key = lambda x : x[2]) # 세번째 값을 기준으로 정렬

usedEdge = 0
res = 0

for x in edge:
    if find(x[0]) != find(x[1]):
        union(x[0], x[1])
        usedEdge += 1
        res += x[2]
    if usedEdge >= v-1:
        break

print(res)