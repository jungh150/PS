from sys import stdin

def find(a):
    global parent
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
        return True
    else:
        return False

while True:
    m, n = map(int, stdin.readline().split())
    if m == 0 and n == 0:
        break
    
    sum = 0
    parent = [i for i in range(m+1)]
    edge = []

    for _ in range(n):
        a, b, c = map(int, stdin.readline().split())
        edge.append((a, b, c))
        sum += c

    edge.sort(key = lambda x : x[2])

    for x in edge:
        if union(x[0], x[1]):
            sum -= x[2]
    print(sum)