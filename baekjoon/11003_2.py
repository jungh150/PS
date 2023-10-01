from sys import stdin
from collections import deque

n, l = map(int, stdin.readline().split())
data = list(map(int, stdin.readline().split()))

window = deque()

for i in range(0, n):
    while (len(window) != 0) and (window[-1][1] > data[i]):
        window.pop()
    window.append((i, data[i]))
    if window[0][0] <= i-l:
        window.popleft()
    print(window[0][1], end=" ")