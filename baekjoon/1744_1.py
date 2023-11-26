from sys import stdin
from queue import PriorityQueue

n = int(stdin.readline())
pos = PriorityQueue()
neg = PriorityQueue()
ans = 0
zero = False

for _ in range(n):
    x = int(stdin.readline())
    if x > 1:
        pos.put(x * (-1))
    elif x < 0:
        neg.put(x)
    elif x == 1:
        ans += 1
    else:
        zero = True

while pos.qsize() > 1:
    ans += (pos.get() * pos.get())
if not pos.empty():
    ans -= pos.get()

while neg.qsize() > 1:
    ans += (neg.get() * neg.get())
if not neg.empty() and not zero:
    ans += neg.get()

print(ans)