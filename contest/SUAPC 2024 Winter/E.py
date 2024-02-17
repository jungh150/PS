from sys import stdin

n = int(stdin.readline())
string = stdin.readline().strip()
m = int(stdin.readline())
edge = []
edgeCheck = [False] * m
for _ in range(m):
    input = stdin.readline()
    edge.append((input[0], input[2]))

for i in range(0, n):
    for j in range(i, n):
        if 