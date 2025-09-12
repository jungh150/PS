import sys
input = sys.stdin.readline

n = int(input())

cnt = [0 for _ in range(10)]
for i in range(1, n + 1):
    tmp = i
    while tmp > 0:
        cnt[tmp % 10] += 1
        tmp //= 10

for i in range(0, 10):
    print(cnt[i], end = ' ')