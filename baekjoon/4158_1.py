from sys import stdin

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
        find = False
        start = 0
        end = len(sy) - 1
        while start <= end:
            mid = (start + end) // 2
            if sy[mid] > x:
                end = mid - 1
            elif sy[mid] < x:
                start = mid + 1
            else:
                find = True
                break
        if(find):
            cnt += 1

    print(cnt)