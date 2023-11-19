from sys import stdin

n, m = map(int, stdin.readline().split())
lsn = list(map(int, stdin.readline().split()))

start = 0
end = 0

for i in lsn:
    if i > start:
        start = i
    end += i

while start <= end:
    mid = (start + end) // 2
    sum = 0
    cnt = 1
    for i in range(n):
        sum += lsn[i]
        if sum > mid:
            sum = lsn[i]
            cnt += 1
    if cnt > m:
        start = mid + 1
    else:
        end = mid - 1

print(start)