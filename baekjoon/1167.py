from sys import stdin
from collections import deque

n = int(stdin.readline())
data = [[] for _ in range(n)]

for _ in range(n):
    input = list(map(int, stdin.readline().split()))
    i = 1
    while input[i] != -1:
        data[input[0]-1].append((input[i], input[i+1]))
        i += 2

def BFS(v):
    que = deque()
    visited[v-1] = True
    que.append(v)
    while que:
        v = que.popleft()
        for i in data[v-1]:
            if not visited[i[0]-1]:
                visited[i[0]-1] = True
                que.append(i[0])
                dst[i[0]-1] = dst[v-1] +  i[1]

dst = [0] * n
visited = [False] * n

BFS(2)

maxIndex = 0
for i in range(n):
    if dst[i] > dst[maxIndex]:
        maxIndex = i

dst = [0] * n
visited = [False] * n

BFS(maxIndex+1)
print(max(dst))