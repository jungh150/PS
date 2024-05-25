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

isCross = False

l1p3 = ccw(x1, y1, x2, y2, x3, y3)
l1p4 = ccw(x1, y1, x2, y2, x4, y4)
l2p1 = ccw(x3, y3, x4, y4, x1, y1)
l2p2 = ccw(x3, y3, x4, y4, x2, y2)

if l1p3 * l1p4 == 0 and l2p1 * l2p2 == 0:
    if min(x1, x2) <= max(x3, x4) and min(x3, x4) <= max(x1, x2) \
       and min(y1, y2) <= max(y3, y4) and min(y3, y4) <= max(y1, y2):
        isCross = True
elif l1p3 * l1p4 <= 0 and l2p1 * l2p2 <= 0:
    isCross = True

if isCross:
    print(1)
else:
    print(0)