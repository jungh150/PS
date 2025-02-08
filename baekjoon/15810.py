from sys import stdin

n, m = map(int, stdin.readline().split())
balloon = list(map(int, stdin.readline().split()))

s = 1
e = 10 ** 12 + 1

while s <= e:
    mid = (s + e) // 2
    tmp = 0
    for x in balloon:
        tmp += mid // x
    if tmp < m:
        s = mid + 1
    else:
        e = mid - 1

print(s)