import sys

N,L = map(int,sys.stdin.readline().split())
bList = list(map(int,sys.stdin.readline().split()))
wList = list(map(int,sys.stdin.readline().split()))
k,p = map(int,sys.stdin.readline().split())

blank = L - sum(wList)
smallThings = 0
for w in wList:
    if w <= blank:
        smallThings += w
BigThings = []
for w in wList:
    if w > blank:
        BigThings.append(w)


if wList[k-1] > blank : # 빈칸보다 큰 경우 ( 순서 유지하며 범위 체크 )
    S = 0
    E = L
    for i in range(k-1):
        if wList[i] > blank :
            S += wList[i]
    for i in range(k, N):
        if wList[i] > blank :
            E -= wList[i]

    if S <= p and E - wList[k-1] >= p :
        print("YES")
    else:
        print("NO")
else: # 빈칸보다 작거나 같은 경우
    S, E = 0,0
    E = blank + smallThings
    nowBook = 0
    lenlen= len(BigThings)
    while(nowBook < lenlen):
        if S <= p and E - wList[k-1] >= p :
            print("YES")
            exit()
        else:
            S += BigThings[nowBook]
            E += BigThings[nowBook]
            nowBook += 1
    if S <= p and E - wList[k-1] >= p :
        print("YES")
        exit()
    print("NO")


