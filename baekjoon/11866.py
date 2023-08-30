import sys
from collections import deque

n, k = map(int, sys.stdin.readline().split())
deq = deque()

for i in range(1, n+1) :
    deq.append(i)

print("<", end = "")

while len(deq) != 0 :
    deq.rotate(-k+1)

    if len(deq) > 1 :
        print(str(deq.popleft()) + ", ", end = "")
    else :
        print(str(deq.popleft()) + ">")