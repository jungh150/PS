from sys import stdin
import math

min, max = map(int, stdin.readline().split())

check = [True] * (max - min + 1)
cnt = 0

# 소수 구하기
rng = int(math.sqrt(max)) + 1
num = [0] * (rng)

for i in range(2, rng):
    num[i] = 1

for i in range(2, int(math.sqrt(rng))+1):
    if num[i] != 0:
        for j in range(i+i, rng, i):
            num[j] = 0

# 소수의 제곱수로 나누어 떨어지는지 체크
for i in range(2, rng):
    if num[i] != 0:
        pow = i * i
        tmp = (min + pow - 1) // pow * pow
        while tmp <= max:
            check[tmp-min] = False
            tmp += pow

for i in range(0, max - min + 1):
    if check[i]:
        cnt += 1

print(cnt)