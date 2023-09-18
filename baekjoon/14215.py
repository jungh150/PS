from sys import stdin

a, b, c = map(int, stdin.readline().split())
max, min1, min2 = 0, 0, 0

if a >= b:
    if a >= c:
        max = a
        min1 = b
        min2 = c
    else: # a < b
        max = c
        min1 = a
        min2 = b
else: # a < b
    if b >= c:
        max = b
        min1 = a
        min2 = c
    else: # b < c
        max = c
        min1 = a
        min2 = b

while max >= min1 + min2:
    max -= 1

print(max + min1 +min2)