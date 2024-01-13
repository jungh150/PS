from sys import stdin
from collections import deque
import copy

sender = [0, 0, 1, 1, 2, 2] # 0:A, 1:B, 2:C
receiver = [1, 2, 0, 2, 0, 1]
visited = [[False for _ in range(201)] for _ in range(201)]
ans = [False] * (201)

def bfs(cap):
    que = deque()
    que.append([0, 0, cap[2]])
    visited[0][0] = True
    ans[cap[2]] = True
    while que:
        cur = que.popleft()
        for i in range(6):
            nxt = copy.deepcopy(cur)
            if nxt[sender[i]] != 0:
                dif = min(nxt[sender[i]], cap[receiver[i]] - nxt[receiver[i]])
                nxt[receiver[i]] += dif
                nxt[sender[i]] -= dif
            if not visited[nxt[0]][nxt[1]]:
                que.append(nxt)
                visited[nxt[0]][nxt[1]] = True
                if nxt[0] == 0:
                    ans[nxt[2]] = True

capacity = list(map(int, stdin.readline().split()))
bfs(capacity)

for i in range(201):
    if ans[i]:
        print(i, end=" ")