import sys
input = sys.stdin.readline

n = int(input())
a = list(map(int, input().split()))

for i in range(n):
    if a[i] == -1:
        idx = i

print(min(a[0:idx]) + min(a[idx + 1:n]))