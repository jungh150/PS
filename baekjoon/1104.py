from sys import stdin

n, k = map(int, stdin.readline().split())
coin = [int(stdin.readline()) for _ in range(n)]
ans = 0

for i in range(n-1, -1, -1):
    ans += k // coin[i]
    k = k % coin[i]

print(ans)