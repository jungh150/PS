from sys import stdin

def gcd(a, b):
    if b == 0:
        return a
    else:
        return gcd(b, a % b)

n = int(stdin.readline())

for _ in range(n):
    a, b = map(int, stdin.readline().split())
    print(int(a * b / gcd(a, b)))