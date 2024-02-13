from sys import stdin

n, m = map(int, stdin.readline().split())
s = []
cnt = 0

for _ in range(n):
    s.append(stdin.readline().strip())

s = set(s)

for _ in range(m):
    string = stdin.readline().strip()
    if string in s:
        cnt += 1

print(cnt)