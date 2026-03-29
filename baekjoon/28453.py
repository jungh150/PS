import sys
input = sys.stdin.readline

n = int(input())
a = list(map(int, input().split()))

for i in range(n):
    if a[i] == 300:
        print(1, end=' ')
    elif a[i] >= 275:
        print(2, end=' ')
    elif a[i] >= 250:
        print(3, end=' ')
    else:
        print(4, end=' ')