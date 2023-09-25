from sys import stdin

paper = [[0] * 100 for _ in range(100)]

n = int(stdin.readline())
count = 0

for i in range(0, n):
    x, y = map(int, stdin.readline().split())
    for j in range(x, x+10):
        for k in range(y, y+10):
            if ((j < 100) and (k < 100)):
                paper[j][k] = 1

for j in range(0, 100):
        for k in range(0, 100):
            if (paper[j][k] == 1):
                count += 1

print(count)