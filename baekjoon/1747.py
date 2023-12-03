from sys import stdin
import math

MAX = 10000001
n = int(stdin.readline())
num = [0] * MAX

for i in range(2, MAX):
    num[i] = i

for i in range(2, int(math.sqrt(MAX))+1):
    if num[i] != 0:
        for j in range(i+i, MAX, i):
            num[j] = 0

for i in range(n, MAX):
    if num[i] != 0:
        isP = True
        tmp = str(num[i])
        for j in range(0, len(tmp)//2):
            if tmp[j] != tmp[len(tmp)-j-1]:
                isP = False
                break
        if isP:
            print(num[i])
            break