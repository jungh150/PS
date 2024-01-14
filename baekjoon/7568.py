from sys import stdin

n = int(stdin.readline())
data = []
ans = []

for _ in range(n):
    x, y = map(int, stdin.readline().split())
    data.append([x, y])

for i in range(n):
    k = 1
    for j in range(n):
        if (data[j][0] > data[i][0]) and (data[j][1] > data[i][1]):
            k += 1
    ans.append(k)

for x in ans:
    print(x, end=" ")