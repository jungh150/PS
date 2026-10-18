import sys

t = int(sys.stdin.readline())

for _ in range(t):
    n = int(sys.stdin.readline())
    myList = [0 for _ in range(10)]
    for _ in range(n):
        b, d = map(int, sys.stdin.readline().split())
        if myList[d-1] < b:
            myList[d-1] = b
        
    if 0 in myList:
        print("MOREPROBLEMS")
    else:
        print(sum(myList))
