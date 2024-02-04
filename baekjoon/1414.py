from sys import stdin

n = int(stdin.readline())
edge = []
parent = [i for i in range(n+1)]
sum = 0

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
        return True
    else:
        return False

for i in range(n):
    input = stdin.readline()
    for j in range(n):
        num = ord(input[j])
        if num != 48: # 0이 아닐 때만 노드 추가
            if num >= 97: # 알파벳 소문자일 경우
                w = num - 96
                sum += w
            else: # 알파벳이 대문자일 경우
                w = num - 38
                sum += w
            edge.append([i+1, j+1, w])

edge.sort(key = lambda x : x[2])

for x in edge:
    if find(x[0]) != find(x[1]):
        union(x[0], x[1])
        sum -= x[2]

isPossible = True
tmp = find(1)
for i in range(2, n+1):
    if find(i) != tmp:
        isPossible = False
        break

if isPossible:
    print(sum)
else:
    print(-1)