from sys import stdin
import math

min, max = map(int, stdin.readline().split())

num = [True] * (max - min + 1)
cnt = 0

for i in range(2, int(math.sqrt(max)) + 1):
    pow = i * i
    tmp = (min + pow - 1) // pow * pow
    while tmp <= max:
        num[tmp-min] = False
        tmp += pow

for i in range(0, max - min + 1):
    if num[i]:
        cnt += 1

print(cnt)