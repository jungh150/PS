import sys
import math
pie = 3.1415926535897932384652
N = int(sys.stdin.readline())

def makeXY(l,r):
    seta = l*2*pie / 3600
    return((r*math.cos(seta)),r*math.sin(seta))

lines = []
for _ in range(N):
    x,y = map(int,sys.stdin.readline().split())
    lines.append((makeXY(x,1000),makeXY(y,1000)))

p1_seta,p1_r = map(int,sys.stdin.readline().split())
p1 = makeXY(p1_seta,p1_r)
p2_seta,p2_r = map(int,sys.stdin.readline().split())
p2 = makeXY(p2_seta,p2_r)


def CCW(a,b,c):
    return (a[0]*b[1] + b[0]*c[1] + c[0]*a[1] ) - (b[0]*a[1] +c[0]*b[1] + a[0]*c[1])

def found_cross(xy,p1p2):
    ccw1 = CCW(xy[0],xy[1],p1p2[0])
    ccw2 = CCW(xy[0],xy[1],p1p2[1])

    if ccw1 * ccw2 < 0 :
        return True
    else:
        return False
    
result = 0
for line in lines:
    if found_cross(line, (p1,p2)):
        result += 1
if result % 2 == 0 :
    print("YES")
else:
    print("NO")

