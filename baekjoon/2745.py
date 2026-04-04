import sys
input = sys.stdin.readline

n, b = input().split()
b = int(b)

tmp = 1
ans = 0
for i in range(len(n) - 1, -1, -1):
    c = n[i]
    if '0' <= c <= '9':
        ans += tmp * (ord(c) - ord('0'))
    else:
        ans += tmp * (ord(c) - ord('A') + 10)
    tmp *= b

print(ans)