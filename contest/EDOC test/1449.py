import sys

n, l = map(int, sys.stdin.readline().split())
leak = list(map(int, sys.stdin.readline().split()))
leak.sort()
tape = [0] * 1000
count = 0

for i in range(0, n) :
    if tape[leak[i]-1] == 0 :
        for j in range(leak[i]-1, leak[i]-1+l) :
            if j < 1000 :
                tape[j] = 1
        count += 1

print(count)