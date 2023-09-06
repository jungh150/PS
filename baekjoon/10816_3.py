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

sang.sort()

for i in range(0, m):
    index = binary_search(card[i], sang, 0, n-1)
    count = 0

    if index != None:
        count = 1

        temp = index - 1
        while temp >= 0:
            if card[i] == sang[temp]:
                count += 1
                temp -= 1
            else:
                break

        temp = index + 1
        while temp < n:
            if card[i] == sang[temp]:
                count += 1
                temp += 1
            else:
                break
    
    print(count, end = " ")