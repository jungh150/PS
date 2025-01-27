import sys

n = int(sys.stdin.readline())
data = []

for i in range (0, n) :
    a, b = map(int, sys.stdin.readline().split())
    data.append([a, b])

data.sort()

for i in range (0, n) :
    print(data[i][0], data[i][1])