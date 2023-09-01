import sys

n = int(sys.stdin.readline())
data = list(map(int, sys.stdin.readline().split()))
sum = 0

data.sort()

for i in range(0, n) :
    sum += (n-i) * data[i]

print(sum)