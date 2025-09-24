import sys
import math
input = sys.stdin.readline

PI = math.pi

def ccw(x1, y1, x2, y2, x3, y3):
    return (x1 * y2 + x2 * y3 + x3 * y1) - (x2 * y1 + x3 * y2 + x1 * y3)

n = int(input())

line = []
for _ in range(n):
    line.append(list(map(int, input().split())))

p1 = list(map(int, input().split()))
p2 = list(map(int, input().split()))

cnt = 0
for l in line:
    x1 = math.cos(2 * PI * l[0] / 3600) * 1000
    y1 = math.sin(2 * PI * l[0] / 3600) * 1000
    x2 = math.cos(2 * PI * l[1] / 3600) * 1000
    y2 = math.sin(2 * PI * l[1] / 3600) * 1000
    p1x = math.cos(2 * PI * p1[0] / 3600) * p1[1]
    p1y = math.sin(2 * PI * p1[0] / 3600) * p1[1]
    p2x = math.cos(2 * PI * p2[0] / 3600) * p2[1]
    p2y = math.sin(2 * PI * p2[0] / 3600) * p2[1]
    if ccw(x1, y1, x2, y2, p1x, p1y) * ccw(x1, y1, x2, y2, p2x, p2y) < 0:
        cnt += 1

if cnt % 2 == 0:
    print("YES")
else:
    print("NO")