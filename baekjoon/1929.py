from sys import stdin
import math

m, n = map(int, stdin.readline().split())
num = [0] * (n+1)

for i in range(2, n+1):
    num[i] = i

for i in range(2, int(math.sqrt(n))+1):
    if num[i] != 0:
        for j in range(i+i, n+1, i):
            num[j] = 0

for i in range(m, n+1):
    if num[i] != 0:
        print(num[i])