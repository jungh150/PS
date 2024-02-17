from sys import stdin

n = int(stdin.readline())
data = list(map(int, stdin.readline().split()))
cnt = [0] * (n+1)

for x in data:
    cnt[x] += 1

