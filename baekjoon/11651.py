from sys import stdin

n = int(stdin.readline())
data = []

for i in range(0, n):
    a, b = map(int, stdin.readline().split())
    data.append([a, b])

data.sort(key = lambda x:(x[1], x[0]))

for i in range(0, n):
    print(data[i][0], data[i][1])