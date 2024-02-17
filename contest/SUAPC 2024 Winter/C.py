from sys import stdin

w, h, k, t = map(int, stdin.readline().split())
div = 998244353
ans = 1

for _ in range(k):
    a, b = map(int, stdin.readline().split())

    x1 = a - t
    if x1 < 1:
        x1 = 1
    x2 = a + t
    if x2 > w:
        x2 = w
    
    y1 = b - t
    if y1 < 1:
        y1 = 1
    y2 = b + t
    if y2 > h:
        y2 = h
    
    ans *= (((x2 - x1 + 1) % div) * ((y2 - y1 + 1)) % div) % div
    ans = ans % div

print(ans)