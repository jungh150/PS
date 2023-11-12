from sys import stdin

n, m = map(int, stdin.readline().split())
map = []

for i in range(n):
    map.append(list(map(int, stdin.readline().strip())))

