from queue import PriorityQueue
from sys import stdin

n = int(stdin.readline())
que = PriorityQueue()

for _ in range(n):
    num = int(stdin.readline())

    if num == 0:
        if que.empty():
            print(0)
        else:
            print(que.get()[1])
    else:
        que.put((abs(num), num))