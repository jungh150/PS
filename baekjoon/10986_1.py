from sys import stdin

def combination(n, r):
    if n == 0:
        return 0
    
    num, den = 1, 1

    for i in range(r+1, n+1):
        num *= i
    for i in range(1, n-r+1):
        den *= i

    ans = int(num/den)

    return ans

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
    ans += combination(count[i], 2)

print(ans)