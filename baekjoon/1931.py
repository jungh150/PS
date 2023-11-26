from sys import stdin

n = int(stdin.readline())
data = []
cnt = 0
end = -1

for _ in range(n):
    s, e = map(int, stdin.readline().split())
    data.append((s, e))

data.sort(key=lambda x:(x[1], x[0]))

for i in range(n):
    if data[i][0] >= end:
        end = data[i][1]
        cnt += 1

print(cnt)