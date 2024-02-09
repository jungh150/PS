from sys import stdin

n = int(stdin.readline())
sum = 0

for i in range(n+1):
    sum += i

print(sum)