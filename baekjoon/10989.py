from sys import stdin

n = int(stdin.readline())
count = [0] * 10000

for i in range(0, n):
    num = int(stdin.readline())
    count[num-1] += 1

for i in range(0, 10000):
    for j in range(0, count[i]):
        print(i+1)