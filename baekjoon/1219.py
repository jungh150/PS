from sys import stdin
import sys

n, start, end, m = map(int, stdin.readline().split())
e = []
dst = [sys.maxsize] * n
check = False

for _ in range(m):
    a, b, c = map(int, stdin.readline().split())
    e.append((a, b, c)) # 도시로 갈 때 교통수단 비용

city = list(map(int, stdin.readline().split())) # 도시에서 벌 수 있는 비용
for i in range(m):
    tmp = list(e[i])
    tmp[2] -= city[tmp[1]]
    e[i] = tuple(tmp)

dst[start] = city[start] * (-1)

for _ in range(n-1):
    for a, b, c in e:
        if dst[a] != sys.maxsize and dst[a] + c < dst[b]:
            dst[b] = dst[a] + c

for _ in range(n):
    for a, b, c in e:
        if dst[a] != sys.maxsize and dst[a] + c < dst[b]:
            dst[b] = sys.maxsize * (-1)
            if b == end:
                check = True
                break

if not check:
    if dst[end] == sys.maxsize:
        print("gg")
    else:
        print(dst[end] * (-1))
else:
    print("Gee")