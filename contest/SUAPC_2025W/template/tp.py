# 3️⃣ 투 포인터 (Two Pointers)

# 정렬된 배열에서 특정 조건을 만족하는 구간을 찾을 때 유용하다.
# 예를 들어, 연속된 부분 합이 특정 값을 만족하는 경우를 찾는 문제에서 많이 사용된다.
def two_pointer(arr, target):
    left, right, curr_sum = 0, 0, 0
    while right < len(arr):
        curr_sum += arr[right]
        while curr_sum > target and left <= right:
            curr_sum -= arr[left]
            left += 1
        if curr_sum == target:
            return (left, right)
        right += 1
    return -1