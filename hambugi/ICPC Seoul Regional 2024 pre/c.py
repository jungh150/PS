import sys
input = sys.stdin.readline

a,b = map(int,input().split())

T = list(input().rstrip())
P = list(input().rstrip())
lst = []

T.reverse()
P.reverse()

def check(i,lst):
    if i == 0:
        return True
    for j in range(i+1,len(lst)):
        if lst[j][0] <= lst[i][1]:
                return False
    return True

start = 0
end = a-1

while True:
    if end == b:
        break
    checkinglst = P[start:end+1]
    if T == checkinglst:
        lst.append((start,end))
    start += 1
    end += 1

# 겹치는게 없을때
if not lst:
    print(b)
    exit()

toplus = 0
left = b

for i in range(len(lst)):
    if i == 0:
        left -= a
        continue
    if lst[i-1][1] >= lst[i][0] and check(i,lst):
        toplus += lst[i-1][1] - lst[i][0] + 1
        left -= a-(lst[i-1][1] - lst[i][0] + 1)

    else:
        left -= a
        
print(toplus+left)

