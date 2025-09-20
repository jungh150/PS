import sys
input = sys.stdin.readline

a, b = map(int, input().split())

cnt = 0

if (a > b):
    a, b = b, a

asq = (a - 1) * (a - 1)
for x in range(0, a - 1):
    ysq = asq - x * x
    if ysq < 0:
        break
    y = int(ysq ** 0.5 + 0.5)
    if y * y == ysq and (x * (b - 1)) % (a - 1) == 0 and (y * (b - 1)) % (a - 1) == 0:
        cnt += 1

if a == b:
    print(cnt)
else:
    print(cnt * 2)