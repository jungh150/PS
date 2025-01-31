from sys import stdin
import math

n = int(stdin.readline())
data = []

if n == 0:
    print(0)
    exit()

for i in range(0, n):
    data.append(int(stdin.readline()))

data.sort()

exc = math.floor(n * 0.15 + 0.5)
sum = 0

for i in range(exc, n-exc):
    sum += data[i]

avg = sum / (n - 2*exc)

print(math.floor(avg + 0.5))