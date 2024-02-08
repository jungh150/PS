from sys import stdin
from collections import deque

t = int(stdin.readline())

for _ in range(t):
    n, a = map(int, stdin.readline().split())
    data = list(map(int, stdin.readline().split()))
    que = deque()
    for i in range(n):
        que.append((i, data[i]))
    
    cnt = 0
    while que:
        now = que.popleft()
        available = True
        for x in que:
            if x[1] > now[1]:
                available = False
                break
        if available:
            cnt += 1
            if now[0] == a:
                print(cnt)
        else:
            que.append(now)