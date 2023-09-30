from sys import stdin

n = int(stdin.readline())
count = 0

startIndex = 1
endIndex = 1
sum = 0

while startIndex <= n:
    if sum < n:
        sum += endIndex
        endIndex += 1
    elif sum > n:
        sum -= startIndex
        startIndex += 1
    else:
        count += 1
        sum += endIndex
        endIndex += 1

print(count)