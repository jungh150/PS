import sys

n, k = map(int, sys.stdin.readline().split())
coin = []
count = 0

for i in range(0, n) :
    coin.append(int(sys.stdin.readline()))

for i in range(0, n) :
    if coin[n-i-1] <= k :
        count += k // coin[n-i-1]
        k = k % coin[n-i-1]

print(count)