import sys

def fact(num) :
    ans = 1
    for i in range(1, num+1) :
        ans *= i

    return ans

n, k = map(int, sys.stdin.readline().split())

ans = fact(n) / (fact(k) * fact(n-k))

print(int(ans))