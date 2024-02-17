from sys import stdin

w, h, k, t = map(int, stdin.readline().split())
div = 998244353
ans = 1

for _ in range(k):
    a, b = map(int, stdin.readline().split())

    x1 = max(1, a - t)
    x2 = min(w, a + t)
    
    y1 = max(1, b - t)
    y2 = min(h, b + t)

    area = ((x2 - x1 + 1) * (y2 - y1 + 1)) % div
    ans = (ans * area) % div

print(ans)