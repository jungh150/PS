import sys
input = sys.stdin.readline

n = int(input())
num = [0 for _ in range(n + 1)]

for i in range(2, n + 1):
    num[i] = num[i - 1] + 1
    if i % 2 == 0:
        num[i] = min(num[i], (num[i // 2] + 1))
    if i % 3 == 0:
        num[i] = min(num[i], (num[i // 3] + 1))

print(num[n])