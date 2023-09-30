from sys import stdin

n = int(stdin.readline())
data = list(map(int, stdin.readline().split()))
count = 0

data.sort()

for i in range(0, n):
    index1 = 0
    index2 = n-1
    num = data[i]

    while index1 < index2:
        sum = data[index1] + data[index2]
        if sum < num:
            index1 += 1
        elif sum > num:
            index2 -= 1
        else:
            if index1 == i:
                index1 += 1
            elif index2 == i:
                index2 -= 1
            else:
                count += 1
                break

print(count)