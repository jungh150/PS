from sys import stdin
import math

MAX = 1000000007
n, m = map(int, stdin.readline().split())
fcnt = 0
bcnt = 0

for _ in range(n):
    a, b = map(int, stdin.readline().split())
    if b == 0:
        fcnt += 1
    else:
        bcnt += 1

if m == 1:
    if bcnt > 1:
        ans = 0
    else:
        ans = 1
else:
    ans = 1
    for _ in range(bcnt - 1):
        ans *= (m - 1)
        ans %= MAX
    ans *= (bcnt + (m - 1) + ((m - 1) ** 2) * fcnt) % MAX
    ans %= MAX

print(ans)