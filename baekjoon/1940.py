from sys import stdin

n = int(stdin.readline())
m = int(stdin.readline())
mat = list(map(int, stdin.readline().split()))

mat.sort()

count = 0
index1 = 0
index2 = n-1
sum = 0

while index1 < index2:
    sum = mat[index1] + mat[index2]
    if sum < m:
        index1 += 1
    elif sum > m:
        index2 -= 1
    else:
        count += 1
        index1 += 1
        index2 -= 1
    
print(count)