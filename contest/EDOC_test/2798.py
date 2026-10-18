import sys

n, m = map(int, sys.stdin.readline().split())
data = list(map(int, sys.stdin.readline().split()))
max = 0

for i in range(0, n-2) :
    for j in range(i+1, n-1) :
        for k in range(j+1, n) :
            sum = data[i] + data[j] + data[k]
            if sum <= m :
                if sum > max :
                    max = sum

print(max)