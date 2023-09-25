from sys import stdin

n, m = map(int, stdin.readline().split())
data = list(map(int, stdin.readline().split()))

sum = [0]
temp = 0
count = [0] * m
count[0] = 1

for i in range(0, n):
    temp += data[i]
    temp %= m
    sum.append(temp)

    count[sum[i+1]] += 1

ans = 0

for i in range(0, m):
    ans += int(count[i]*(count[i]-1)/2)

print(ans)