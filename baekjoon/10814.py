from sys import stdin

n = int(stdin.readline())
data = []

for i in range(0, n):
    num, name = map(str, stdin.readline().split())
    
    data.append([])
    data[i].append(int(num))
    data[i].append(name)

data.sort(key=lambda x:x[0])

for i in range(0, n):
    print(data[i][0], data[i][1], sep=" ")