import sys

n, k = map(int, sys.stdin.readline().split())

ans = 1

for i in range(k+1, n+1) :
    ans *= i

for i in range(1, n-k+1) :
    ans /= i

print(int(ans))