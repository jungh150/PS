from sys import stdin
from queue import PriorityQueue

n = int(stdin.readline())
ans = 0
que = PriorityQueue()

for _ in range(n):
    que.put(int(stdin.readline()))

while que.qsize() > 1:
    x1 = que.get()
    x2 = que.get()
    que.put(x1 + x2)
    ans += (x1 + x2)

if n == 1:
    print(0)
else:
    print(ans)