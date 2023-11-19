from sys import stdin

def binary_search(target, data, start, end):
    if start > end:
        return None

    mid = (start + end) // 2

    if data[mid] == target:
        return mid
    elif data[mid] > target:
        end = mid - 1
    else:
        start = mid + 1
    
    return binary_search(target, data, start, end)

n = int(stdin.readline())
a = list(map(int, stdin.readline().split()))
m = int(stdin.readline())
num = list(map(int, stdin.readline().split()))

a.sort()

for i in range(0, m):
    if binary_search(num[i], a, 0, n-1) == None:
        print(0)
    else:
        print(1)