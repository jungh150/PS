from sys import stdin

n, k = map(int, stdin.readline().split())
data = list(map(int, stdin.readline().split()))

data.sort()

print(data[k-1])