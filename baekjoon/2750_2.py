from sys import stdin

n = int(stdin.readline())
data = []

for i in range(n):
    data.append(int(stdin.readline()))

for i in range(0, n-1):
    for j in range(0, n-1-i):
        if data[j] > data[j+1]:
            temp = data[j]
            data[j] = data[j+1]
            data[j+1] = temp

for i in data:
    print(i)