import sys
input = sys.stdin.readline

tmp = 0
ans = 0

for _ in range(4):
    a, b = map(int, input().split())
    tmp -= a
    tmp += b
    ans = max(ans, tmp)

print(ans)