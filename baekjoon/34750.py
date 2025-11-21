import sys
input = sys.stdin.readline

n = int(input())
a = 0

if n >= 1000000:
    a = n * 20 // 100
elif n >= 500000:
    a = n * 15 // 100
elif n >= 100000:
    a = n * 10 // 100
else:
    a = n * 5 // 100

print(a, n - a)