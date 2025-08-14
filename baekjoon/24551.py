import sys
input = sys.stdin.readline

n = int(input())
a = [11, 111, 11111, 1111111, 11111111111, 1111111111111, 11111111111111111]

ans = 0
for mask in range(1, 1 << len(a)):
    tmp = 1
    bitcnt = 0
    
    for i in range(len(a)):
        if mask & (1 << i):
            tmp *= a[i]
            bitcnt += 1
            if tmp > n:
                break
    
    if tmp <= n:
        if bitcnt % 2 == 1:
            ans += n // tmp
        else:
            ans -= n // tmp

print(ans)