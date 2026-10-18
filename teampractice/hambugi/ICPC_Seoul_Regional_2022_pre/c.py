import sys

n = int(sys.stdin.readline())
a_list = list(map(int, sys.stdin.readline().split()))
a_list.sort(reverse=True)

sums = sum(a_list)
ansColumn_height = sums // n
plusColumn_num = sums % n

diff = 0
for i in range(plusColumn_num):
    diff += abs(a_list[i] - (ansColumn_height+1))
for i in range(plusColumn_num,n):
    diff += abs(a_list[i] - (ansColumn_height))

print(diff//2)