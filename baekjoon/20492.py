import sys
input = sys.stdin.readline

n = int(input())
print(int(n * 0.78), end=" ")
print(int(n * 0.8 + n * 0.2 * 0.78))