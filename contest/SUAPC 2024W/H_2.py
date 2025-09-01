from sys import stdin

n = int(stdin.readline())
s = []
num = [[] for _ in range(n+1)]
fin = 0

for i in range(1, n+1):
    num[i].append(i)

for _ in range(n):
    s.append(stdin.readline().strip())

for _ in range(n - 1):
    i, j = map(int, stdin.readline().split())
    num[i].extend(num[j])
    fin = i

for i in num[fin]:
    print(s[i-1], end='')