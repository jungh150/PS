from sys import stdin

n = int(stdin.readline())
a = list(map(int, stdin.readline().split()))
m = int(stdin.readline())
data = list(map(int, stdin.readline().split()))

a.sort()

for x in data:
    find = False
    start = 0
    end = len(a) - 1
    while start <= end:
        mid = (start + end) // 2
        if a[mid] > x:
            end = mid - 1
        elif a[mid] < x:
            start = mid + 1
        else:
            find = True
            break
    if(find):
        print(1)
    else:
        print(0)