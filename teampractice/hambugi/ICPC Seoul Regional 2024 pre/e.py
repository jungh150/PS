import sys

N, M = map(int, sys.stdin.readline().split())

A = []
for _ in range(N):
    alist = list(map(int,sys.stdin.readline().split()))
    A.append(alist)
B = []
for _ in range(N):
    blist = list(map(int,sys.stdin.readline().split()))
    B.append(blist)    

diff = []
for i in range(N):
    diffList = []
    for j in range(N):
        diffList.append(abs(A[i][j]-B[i][j]))
    diff.append(diffList)

diffMax = []
for i in range(N):
    maxNum = 0
    for j in range(N):
        maxNum = max(maxNum, diff[j][i])
    diffMax.append(maxNum)

result = 0
dreamNum = list(map(int,sys.stdin.readline().split()))
for i in range(M):
    result += diffMax[dreamNum[i]-1]
print(result)

