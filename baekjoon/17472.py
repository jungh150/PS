from sys import stdin
from collections import deque

dr = [0, 1, 0, -1]
dc = [1, 0, -1, 0]
    # 상 우 하 좌

n, m = map(int, stdin.readline().split())
data = [] # 지도
visited = [[False for _ in range(m)] for _ in range(n)]
edge = []
ans = 0
iNum = 1 # 섬 번호 넘버링

for _ in range(n):
    data.append(list(map(int, stdin.readline().split())))

def bfs(i, j):
    que = deque()
    que.append([i, j])
    visited[i][j] = True
    data[i][j] = iNum
    while que:
        r, c = que.popleft()
        for i in range(4):
            nr = r + dr[i]
            nc = c + dc[i]
            if nr >= 0 and nr < n and nc >= 0 and nc < m:
                if not visited[nr][nc] and data[nr][nc] != 0:
                    visited[nr][nc] = True
                    data[nr][nc] = iNum
                    que.append([nr, nc])

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
    for j in range(m):
        if not visited[i][j] and data[i][j] != 0:
            bfs(i, j)
            iNum += 1

parent = [i for i in range(iNum)]

for i in range(n):
    pre = -1 # 전 column 값
    for j in range(m):
        if data[i][j] != 0:
            if pre != -1 and data[i][pre] != data[i][j] and (j - pre - 1) >=2:
                edge.append((data[i][pre], data[i][j], (j - pre - 1)))
            pre = j

for j in range(m):
    pre = -1 # 전 row 값
    for i in range(n):
        if data[i][j] != 0:
            if pre != -1 and data[pre][j] != data[i][j] and (i - pre - 1) >=2:
                edge.append((data[pre][j], data[i][j], (i - pre - 1)))
            pre = i

edge.sort(key = lambda x : x[2])

for x in edge:
    if union(x[0], x[1]):
        ans += x[2]

isPossible = True
tmp = find(1)
for i in range(2, iNum):
    if find(i) != tmp:
        isPossible = False
        break

if isPossible:
    print(ans)
else:
    print(-1)