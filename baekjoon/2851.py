from sys import stdin

sum = 0
mush = []
mushSum = [0]

for i in range(0, 10):
    mush.append(int(stdin.readline()))
    sum += mush[i]
    mushSum.append(sum)

for i in range(1, 11):
    if mushSum[i] >= 100:
        if (mushSum[i] - 100) <= (100 - mushSum[i-1]):
            print(mushSum[i])
            break
        else:
            print(mushSum[i-1])
            break
    else:
        if i == 10:
            print(mushSum[i])