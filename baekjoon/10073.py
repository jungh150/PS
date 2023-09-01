import sys

n = int(sys.stdin.readline())
data = []
sum = 0

for i in range(0, n) :
    num = int(sys.stdin.readline())
    if num == 0 :
        del data[-1]
    else :
        data.append(num)

for i in range(0, len(data)) :
    sum += data[i]

print(sum)