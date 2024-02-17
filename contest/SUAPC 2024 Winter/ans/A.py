import sys
input = sys.stdin.readline

Q = int(input())
for _ in range(Q):
    Ta, Tb, Va, Vb = map(int, input().split())
    cnt = 0

    resA, resB = 0, 0
    if Ta*Va > Tb*Vb:
        resB = Tb*Vb
        while Ta*cnt+1<resB:
            cnt+=1
        resA = Ta*cnt
        remaining_Va = Va - cnt
        while remaining_Va>0:
            if resA + Ta > resB + Ta:
                resB += Ta
                remaining_Va-=1
            else:
                resA += Ta
                remaining_Va-=1
        print(max(resA, resB))
    else:
        print(Tb*Vb)
