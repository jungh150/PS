from sys import stdin

n = int(stdin.readline())
data = []

for i in range(n):
    data.append((int(stdin.readline()), i))

data.sort()
max = 0

for i in range(n):
    if data[i][1] - i > max:
        max = data[i][1] - i

print(max + 1)