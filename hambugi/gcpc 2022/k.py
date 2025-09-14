import sys
input = sys.stdin.readline

n,m = map(int,input().split())
num = 0
strr = list(input().rstrip())

if strr[0] == 'L':
    for i in range(1,n):
        if strr[i] ==strr[i-1]:
            num += 1
else:
    num += 1
    for i in range(1,n):
        if strr[i] ==strr[i-1]:
            num += 1
if m-num < 0:
    print(0)

else:
    print(m-num)