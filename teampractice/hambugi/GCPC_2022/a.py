import sys
import math

a, b = map(int,sys.stdin.readline().split())
A = a -1 
B = b -1

result = 2 # x=0 / y=0

def isThisSqrt(n):
    if n % 1 == 0:
        return True
    else:
        return False
    
for i in range(1,A):
    doubled_x = i**2
    x = i
    y = ( A**2 - doubled_x) **(1/2)
    if isThisSqrt(y):
        if B % (A // math.gcd(x,int(y))) == 0 :
            result += 2

if A == B :
    print(result // 2)
else:
    print(result)