import sys

D,H,W = map(int, sys.stdin.readline().split())

for _ in range(D):
    go, come = map(str,sys.stdin.readline().split())

    result_go = 'N'
    result_come = 'N'
    if go == 'Y' or W == 0 :
        result_go = 'Y'
        H -= 1
        W += 1

    if come == 'Y' or H == 0 :
        result_come = 'Y'
        H += 1
        W -= 1

    print(result_go,result_come)