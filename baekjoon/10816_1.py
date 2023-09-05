import sys

n = int(sys.stdin.readline())
sang = list(map(int, sys.stdin.readline().split()))
m = int(sys.stdin.readline())
card = list(map(int, sys.stdin.readline().split()))

sang.sort()

for i in range(0, m) :
    count = 0

    for j in range(0, n) :
        if card[i] == sang[j] :
            count += 1
    
    print(count, end = " ")