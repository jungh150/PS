from sys import stdin
import math

n = int(stdin.readline())
ans = n

for i in range(2, int(math.sqrt(n)) + 1):
    if n % i == 0:
        ans = ans - ans // i
        while n % i == 0:
            n = n // i

if n > 1:
    ans = ans - ans // n

print(ans)