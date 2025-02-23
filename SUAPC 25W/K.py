import sys
input = sys.stdin.readline

n,m = map(int,input().split())
lst = []
for i in range(m):
    a,b = map(int,input().split())
    lst.append((a,b))
def count(i):
    price = lst[i][0]
    num = lst[i][1]
    while True:
        for i in range(i+1,m):
            