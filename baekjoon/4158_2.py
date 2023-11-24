from sys import stdin
from bisect import bisect_left, bisect_right

while(True):
    n, m = map(int, stdin.readline().split())
    sg, sy = [], []
    cnt = 0

    if (n==0 and m==0):
        break

    for _ in range(n):
        sg.append(int(stdin.readline()))
    for _ in range(m):
        sy.append(int(stdin.readline()))

    for x in sg:
        if(bisect_right(sy, x) - bisect_left(sy, x) > 0):
            cnt += 1

    print(cnt)