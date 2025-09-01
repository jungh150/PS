from sys import stdin
import math
import sys

n = int(stdin.readline())
x = []
y = []
ans = sys.maxsize

for _ in range(n):
    a, b = map(int, stdin.readline().split())
    x.append(a)
    y.append(b)

for i in range(n):
    for j in range(i + 1, n):
        d = math.sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2))
        a = y[j] - y[i]
        b = x[i] - x[j]
        c = x[j] * y[i] - x[i] * y[j]
        for k in range(n):
            if k == i or k == j:
                continue
            dst = (a * x[k] + b * y[k] + c) / math.sqrt(a * a + b * b)
            if dst < 0:
                dst = dst * (-1)
            if dst < ans:
                ans = dst

print(ans)