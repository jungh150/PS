from sys import stdin
from bisect import bisect_left, bisect_right

n = int(stdin.readline())
sang = list(map(int, stdin.readline().split()))
m = int(stdin.readline())
card = list(map(int, stdin.readline().split()))

sang.sort()

for i in range(0, m):
    print(bisect_right(sang, card[i]) - bisect_left(sang, card[i]), end = " ")