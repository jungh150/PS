import sys
from bisect import bisect_right, bisect_left

n = int(sys.stdin.readline())
sang = list(map(int, sys.stdin.readline().split()))
m = int(sys.stdin.readline())
card = list(map(int, sys.stdin.readline().split()))

sang.sort()

for i in range(0, m):
    count = bisect_right(sang, card[i]) - bisect_left(sang, card[i])
    print(count, end = " ")
    