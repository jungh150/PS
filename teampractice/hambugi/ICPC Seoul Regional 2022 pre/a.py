import sys

n = int(sys.stdin.readline())
nlist = list(map(int, sys.stdin.readline().split()))

left = nlist[0]
right = nlist[1]

for i in range(2,n):
    if left <= right :
        left += nlist[i]
    else :
        right += nlist[i]

remains = abs(left - right)
chus = [100,50,20,10,5,2,1]

result = 0
for chu in chus:
    if remains == 0 :
        break
    getable = remains // chu

    result += getable
    remains -= chu * getable

print(result)
