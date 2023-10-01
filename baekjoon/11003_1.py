from sys import stdin
from collections import deque

n, l = map(int, stdin.readline().split())
data = list(map(int, stdin.readline().split()))

window = deque()

for i in range(0, l):
    window.append(data[i])
    print(min(window), end=" ")

for i in range(l, n):
    window.popleft()
    window.append(data[i])
    print(min(window), end=" ")