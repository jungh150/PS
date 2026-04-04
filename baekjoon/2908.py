import sys
input = sys.stdin.readline

s1, s2 = input().split()

s1 = s1[::-1]
s2 = s2[::-1]

print(max(int(s1), int(s2)))