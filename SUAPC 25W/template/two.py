import bisect

arr = [1, 3, 5, 7, 9]
print(bisect.bisect_left(arr, 4))  # 2 (4가 들어갈 위치)
print(bisect.bisect_right(arr, 4)) # 2 (4보다 큰 숫자가 나오는 첫 위치)




##재귀

def binary_search_recursive(arr, target, left, right):
    if left > right:
        return -1  # 값이 없음

    mid = (left + right) // 2

    if arr[mid] == target:
        return mid
    elif arr[mid] > target:
        return binary_search_recursive(arr, target, left, mid - 1)
    else:
        return binary_search_recursive(arr, target, mid + 1, right)

# 예제 실행
arr = [1, 3, 5, 7, 9, 11]
target = 5
index = binary_search_recursive(arr, target, 0, len(arr) - 1)
print(index)  # 출력: 2








## 반복문


def binary_search_iterative(arr, target):
    left, right = 0, len(arr) - 1

    while left <= right:
        mid = (left + right) // 2  # 중간 인덱스
        if arr[mid] == target:
            return mid
        elif arr[mid] > target:
            right = mid - 1  # 왼쪽 절반 탐색
        else:
            left = mid + 1  # 오른쪽 절반 탐색

    return -1  # 값이 없을 경우

# 예제 실행
arr = [1, 3, 5, 7, 9, 11]
target = 7
index = binary_search_iterative(arr, target)
print(index)  # 출력: 3
