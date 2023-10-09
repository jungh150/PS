from collections import deque
from sys import stdin

size = int(stdin.readline())
que = deque()

while True:
    data = int(stdin.readline())

    if data == -1:
        break
    elif data == 0:
        que.pop()
    else:
        if len(que) < size:
            que.appendleft(data)

if len(que) == 0:
    print("empty")
else:
    while len(que) > 0:
        print(que.pop(), end=" ")