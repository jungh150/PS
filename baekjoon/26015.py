import sys
input = sys.stdin.readline

n = int(input())
ans = -200 * (1 - (- 0.5) ** (n - 1)) / 3 + 100

print(ans, end = ' ')
print(100 - ans)