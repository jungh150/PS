from sys import stdin

n, m = map(int, stdin.readline().split())
data = []

for _ in range(0, n):
    data.append(list(map(int, stdin.readline().split())))

sum = [[0] * (n+1)]
for i in range(1, n+1):
    sum.append([0])
    for j in range(1, n+1):
        sum[i].append(sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + data[i-1][j-1])

for _ in range(0, m):
    x1, y1, x2, y2 = map(int, stdin.readline().split())
    print(sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1])