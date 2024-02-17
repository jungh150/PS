from sys import stdin
import gc

n = int(stdin.readline())
s = [[] for _ in range(n)]
fin = 0

for i in range(n):
    s[i].append(stdin.readline().strip())

for _ in range(n-1):
    i, j = map(int, stdin.readline().split())
    s[i-1].extend(s[j-1])
    fin = i
    for x in s[j-1]:
        del(x)
    gc.collect()

print(''.join(s[fin-1]))