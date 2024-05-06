import sys
input = sys.stdin.readline

n = int(input())
data = list(map(int, input().split()))

l = [0 for _ in range(n)]
l[0] = data[0]
res = l[0]

for i in range(1, n):
    l[i] = max(data[i], l[i - 1] + data[i])
    res = max(res, l[i]) # 수를 제거하지 않았을 때의 최댓값

r = [0 for _ in range(n)]
r[n - 1] = data[n - 1]

for i in range(n - 2, -1, -1):
    r[i] = max(data[i], r[i + 1] + data[i])

for i in range(1, n - 1):
    tmp = l[i - 1] + r[i + 1] # 수를 제거했을 때의 최댓값
    res = max(res, tmp)

print(res)