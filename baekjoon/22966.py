import sys
input = sys.stdin.readline

n = int(input())
data = []

for i in range(n):
    a, b = input().split()
    data.append([int(b), a])

data.sort()

print(data[0][1])