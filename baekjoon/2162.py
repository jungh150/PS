import sys
input = sys.stdin.readline

n = int(input())
parent = [-1] * n
l = []

def ccw(x1, y1, x2, y2, x3, y3):
    ccw = (x1 * y2 + x2 * y3 + x3 * y1) - (x2 * y1 + x3 * y2 + x1 * y3)
    if ccw > 0:
        return 1
    elif ccw < 0:
        return -1
    else:
        return 0

def isCross(x1, y1, x2, y2, x3, y3, x4, y4):
    cross = False

    l1p3 = ccw(x1, y1, x2, y2, x3, y3)
    l1p4 = ccw(x1, y1, x2, y2, x4, y4)
    l2p1 = ccw(x3, y3, x4, y4, x1, y1)
    l2p2 = ccw(x3, y3, x4, y4, x2, y2)

    if l1p3 * l1p4 == 0 and l2p1 * l2p2 == 0:
        if min(x1, x2) <= max(x3, x4) and min(x3, x4) <= max(x1, x2) \
           and min(y1, y2) <= max(y3, y4) and min(y3, y4) <= max(y1, y2):
            cross = True
    elif l1p3 * l1p4 <= 0 and l2p1 * l2p2 <= 0:
        cross = True

    return cross

def find(a):
    if parent[a] < 0:
        return a
    parent[a] = find(parent[a])
    return parent[a]

def union(a, b):
    p = find(a)
    q = find(b)
    if p == q:
        return
    parent[p] += parent[q]
    parent[q] = p

for i in range(n):
    l.append(list(map(int, input().split())))
    for j in range(i):
        if isCross(l[i][0], l[i][1], l[i][2], l[i][3], l[j][0], l[j][1], l[j][2], l[j][3]):
            union(i, j)

cnt = 0
ans = 0

for i in range(n):
    if parent[i] < 0:
        cnt += 1
        ans = min(ans, parent[i])

print(cnt)
print(ans * (-1))