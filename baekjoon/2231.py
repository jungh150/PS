from sys import stdin

n = int(stdin.readline())

for m in range(1, n+1):
    sum = m
    temp = m

    while temp != 0:
        sum += temp % 10
        temp //= 10
    
    if sum == n:
        print(m)
        break
    
    if m == n:
        print(0)