import sys
input = sys.stdin.readline

n = int(input())
x = [0] * (n + 1)
y = [0] * (n + 1)

for i in range(n):
    x[i], y[i] = map(int, input().split())

x[n] = x[0]
y[n] = y[0]

ans = 0
for i in range(n):
    ans += (x[i] * y[i + 1] - x[i + 1] * y[i])

print(round(abs(ans / 2), 1))