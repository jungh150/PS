from sys import stdin

n = int(stdin.readline())
data = list(map(int, stdin.readline().strip()))
sum = 0

for i in range(0, n):
    sum += data[i]

print(sum)