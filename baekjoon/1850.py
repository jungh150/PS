from sys import stdin

def gcd(a, b):
    if b == 0:
        return a
    else:
        return gcd(b, a % b)

a, b = map(int, stdin.readline().split())
cnt = gcd(a, b)
print("1" * cnt)