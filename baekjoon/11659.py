from sys import stdin

n, m = map(int, stdin.readline().split())
data = list(map(int, stdin.readline().split()))

sum = [0]
temp = 0

for k in range(0, n):
    temp += data[k]
    sum.append(temp)

for k in range(0, m):
    i, j = map(int, stdin.readline().split())
    print(sum[j] - sum[i-1])