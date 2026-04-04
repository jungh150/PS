import sys
input = sys.stdin.readline

p = [[False for _ in range(100)] for _ in range(100)]

n = int(input())
for _ in range(n):
    a, b = map(int, input().split())
    for i in range(a, a + 10):
        for j in range(b, b + 10):
            p[i][j] = True

ans = 0
for i in range(100):
    for j in range(100):
        if p[i][j]:
            ans += 1

print(ans)