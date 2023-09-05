import sys

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

n = int(sys.stdin.readline())
sang = list(map(int, sys.stdin.readline().split()))
m = int(sys.stdin.readline())
card = list(map(int, sys.stdin.readline().split()))
have = [0] * m

card.sort()

for i in range(0, n):
    result = binary_search(sang[i], card, 0, m-1)
    
    if result != None:
        

    print(count, end = " ")