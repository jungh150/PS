import sys

n = int(sys.stdin.readline())
data = []

for i in range(0, n) :
    data.append(int(sys.stdin.readline()))

data.sort()

for i in range(0, n) :
    print(data[i])