#최장 부분 증가 수열
# 
import bisect

def LIS(arr):
    lis = []
    for num in arr:
        idx = bisect.bisect_left(lis, num)
        if idx == len(lis):
            lis.append(num)
        else:
            lis[idx] = num
    return len(lis)
