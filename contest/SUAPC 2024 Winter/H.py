# 메모리 초과

from sys import stdin

n = int(stdin.readline())
s = []
fin = 0

for _ in range(n):
    s.append(list(stdin.readline().strip()))

for _ in range(n-1):
    i, j = map(int, stdin.readline().split())
    s[i-1].extend(s[j-1])
    fin = i

print(''.join(s[fin-1]))