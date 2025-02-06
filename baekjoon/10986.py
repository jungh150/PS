from sys import stdin

n, m = map(int, stdin.readline().split())
data = list(map(int, stdin.readline().split()))

temp = 0
count = [0] * m
count[0] = 1

for i in range(0, n):
    temp += data[i]
    temp %= m
    count[temp] += 1

ans = 0
for i in range(0, m):
    ans += int(count[i]*(count[i]-1)/2)

print(ans)