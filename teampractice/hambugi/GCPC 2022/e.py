import sys

n = int(sys.stdin.readline())
A_n = (-100)*(1-((-1/2)**(n-1)))/(3/2) + 100
print(A_n, 100-A_n)