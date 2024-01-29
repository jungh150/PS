from sys import stdin
import sys

n, m = map(int, stdin.readline().split())
e = []
dst = [sys.maxsize] * (n+1)
check = False

for _ in range(m):
    a, b, c = map(int, stdin.readline().split())
    e.append((a, b, c))

dst[1] = 0

for _ in range(n-1):
    for a, b, c in e:
        if dst[a] != sys.maxsize and dst[a] + c < dst[b]:
            dst[b] = dst[a] + c

for _ in range(n-1):
    for a, b, c in e:
        if dst[a] != sys.maxsize and dst[a] + c < dst[b]:
            check = True
            break

if not check:
    for i in range(2, n+1):
        if dst[i] == sys.maxsize:
            print(-1)
        else:
            print(dst[i])
else:
    print(-1)