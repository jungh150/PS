from sys import stdin
import sys

sys.setrecursionlimit(10000)

num = int(stdin.readline())
odd = [1, 3, 5, 7, 9]

def isPrime(n):
    for i in range(2, n//2 + 2):
        if n % i == 0:
            return False
    return True


def DFS(n):
    if len(str(n)) == num:
        print(n)
    else:
        for i in odd:
            if isPrime(10*n + i):
                DFS(10*n + i)

DFS(2)
DFS(3)
DFS(5)
DFS(7)