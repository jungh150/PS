import sys

n = int(sys.stdin.readline())
sang = list(map(int, sys.stdin.readline().split()))
m = int(sys.stdin.readline())
card = list(map(int, sys.stdin.readline().split()))

count = {}

for i in sang:
    if i in count:
        count[i] += 1
    else:
        count[i] = 1
    
for i in card:
    if i in count:
        print(count[i], end = " ")
    else:
        print(0, end = " ")