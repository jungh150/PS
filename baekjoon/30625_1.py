from sys import stdin

n, m = map(int, stdin.readline().split())
dance = []

for _ in range(n):
    a, b = map(int, stdin.readline().split())
    if b == 0:
        dance.append(1)
    else:
        dance.append(m - 1)

ans = 1
for i in range(n):
    ans *= dance[i]

for x in range(n):
    tmp = 1
    for i in range(n):
        if i == x:
            tmp *= (m - dance[i])
        else:
            tmp *= dance[i]
    ans += tmp

print(ans)