from sys import stdin

n = int(stdin.readline())
date = [0 for _ in range(32)]
isPossible = True

for _ in range(n):
    a, b = map(int, stdin.readline().split())
    for i in range(a, b):
        date[i] += 1

k = int(stdin.readline())

for i in range(1, 32):
    if date[i] > k:
        isPossible = False
        break

if isPossible:
    print(1)
else:
    print(0)