import sys

n = int(sys.stdin.readline())
data = []

for i in range(0, n) :
    data.append(int(sys.stdin.readline()))

#data.sort()

for i in range(1, n) :
    temp = data[i]
    for j in range(0, i) :
        if temp < data[i-j-1] :
            data[i-j] = data[i-j-1]
            data[i-j-1] = temp
        else :
            data[i-j] = temp
            break

for i in range(0, n) :
    print(data[i])