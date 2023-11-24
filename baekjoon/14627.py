from sys import stdin

s, c = map(int, stdin.readline().split())
pa = []
sum = 0

for i in range(s):
    pa.append(int(stdin.readline()))
    sum += pa[i]

start = 1
end = max(pa)

while start <= end:
    mid = (start + end) // 2
    cnt = 0
    for i in range(s):
        cnt += pa[i] // mid
    if cnt >= c:
        start = mid + 1
    else:
        end = mid - 1

print(sum - c*end)