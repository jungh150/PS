from sys import stdin

n = int(stdin.readline())
data = list(map(int, stdin.readline().split()))
sum = 0
max = 0

for i in range(0, n):
    sum += data[i]
    if data[i] > max:
        max = data[i]

avg = (sum * 100 / max) / n

print(avg)