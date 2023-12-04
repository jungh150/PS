from sys import stdin

n = int(stdin.readline())
a = list(map(int, stdin.readline().split()))
b = list(map(int, stdin.readline().split()))
k = list(map(float, stdin.readline().split()))
kint = [int(i * 10) for i in k]
adr = 0

for i in range(n):
    if kint[i] >= 10:
        adr += int(a[i] * kint[i] / 10)
        adr -= b[i]
    else:
        adr -= int(b[i] * kint[i] / 10)
        adr += a[i]

print(adr)