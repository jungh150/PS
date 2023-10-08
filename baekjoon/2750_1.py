from sys import stdin

n = int(stdin.readline())
data = []

for i in range(0, n):
    data.append(int(stdin.readline()))

data.sort()

for i in range(0, n):
    print(data[i])