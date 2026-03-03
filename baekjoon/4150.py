import sys
input = sys.stdin.readline

n = int(input())

a = 1
b = 1

if n <= 2:
    print(1)
    exit(0)

c = 0
for i in range(n - 2):
    c = a + b
    a = b
    b = c

print(c)