import sys
input = sys.stdin.readline

p = [0 for _ in range(101)]

p[1] = p[2] = p[3] = 1
p[4] = p[5] = 2
for i in range(6, 101):
    p[i] = p[i - 1] + p[i - 5]

t = int(input())
for _ in range(t):
    n = int(input())
    print(p[n])