from sys import stdin
import math

m, n = map(int, stdin.readline().split())
num = [0] * 10000001
cnt = 0

for i in range(2, 10000001):
    num[i] = i

for i in range(2, int(math.sqrt(10000001))+1):
    if num[i] != 0:
        for j in range(i+i, 10000001, i):
            num[j] = 0

for i in range(2, 10000001):
    if num[i] != 0:
        tmp = num[i]
        while tmp * num[i] <= n:
            if tmp * num[i] >= m:
                cnt += 1
            tmp = tmp * num[i]

print(cnt)