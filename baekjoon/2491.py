import sys
input = sys.stdin.readline

n = int(input())
data = list(map(int, input().split()))
dif = [0 for _ in range(n - 1)]

for i in range(n - 1):
    dif[i] = data[i + 1] - data[i]

maxP = tmp = 0
for i in range(n-1):
    if dif[i] >= 0:
        tmp += 1
        if tmp > maxP:
            maxP = tmp
    else:
        tmp = 0

maxM = tmp = 0
for i in range(n-1):
    if dif[i] <= 0:
        tmp += 1
        if tmp > maxM:
            maxM = tmp
    else:
        tmp = 0

print(max(maxP, maxM) + 1)