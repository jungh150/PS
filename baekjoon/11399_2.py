from sys import stdin

n = int(stdin.readline())
data = list(map(int, stdin.readline().split()))

for i in range(1, n):
    value = data[i]
    for j in range(i-1, -1, -1):
        if(data[j] > value):
            data[j+1] = data[j]
        else:
            data[j+1] = value
            break
        if(j==0):
            data[0] = value

sum = 0
for i in range(0, n):
    sum += (n-i) * data[i]

print(sum)