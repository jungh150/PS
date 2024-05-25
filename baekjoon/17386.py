import sys
input = sys.stdin.readline

x1, y1, x2, y2 = map(int, input().split())
x3, y3, x4, y4 = map(int, input().split())

def ccw(x1, y1, x2, y2, x3, y3):
    ccw = (x1 * y2 + x2 * y3 + x3 * y1) - (x2 * y1 + x3 * y2 + x1 * y3)
    if ccw > 0:
        return 1
    elif ccw < 0:
        return -1
    else:
        return 0

l1p3 = ccw(x1, y1, x2, y2, x3, y3)
l1p4 = ccw(x1, y1, x2, y2, x4, y4)
l2p1 = ccw(x3, y3, x4, y4, x1, y1)
l2p2 = ccw(x3, y3, x4, y4, x2, y2)

if l1p3 * l1p4 < 0 and l2p1 * l2p2 < 0:
    print(1)
else:
    print(0)