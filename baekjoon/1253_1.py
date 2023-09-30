from sys import stdin

def greatNum(data, index1, index2, num):
    while index1 < index2:
        sum = data[index1] + data[index2]
        if sum < num:
            index1 += 1
        elif sum > num:
            index2 -= 1
        else:
            return True
    return False

n = int(stdin.readline())
data = list(map(int, stdin.readline().split()))
count = 0

data.sort()

if n >= 3 and data[2] == 0:
    count += 2

for i in range(1, n):
    if greatNum(data, 0, i-1, data[i]):
        count += 1

print(count)