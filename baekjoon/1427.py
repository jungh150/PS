from sys import stdin

data = list(map(int, stdin.readline().strip()))
n = len(data)

for i in range(0, n-1):
    maxIndex = i
    for j in range(i+1, n):
        if data[j] > data[maxIndex]:
            maxIndex = j
    temp = data[maxIndex]
    data[maxIndex] = data[i]
    data[i] = temp

for i in data:
    print(i, end="")