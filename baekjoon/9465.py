import sys
input = sys.stdin.readline

t = int(input())

for _ in range(t):
    n = int(input())
    stk = []
    dp = [0] * (n + 1)
    chk = [[1] * (n + 1) for _ in range(2)]
    
    stk.append([0] + list(map(int, input().split())))
    stk.append([0] + list(map(int, input().split())))
    
    higher = 0
    lower = 1
    if stk[0][1] < stk[1][1]:
        higher = 1
        lower = 0
    dp[1] = stk[higher][1]
    chk[higher][1] = 0
    for i in range(2, n + 1):
        tmp1 = stk[1][i - 1] * chk[1][i - 2] + stk[0][i]
        tmp2 = stk[0][i - 1] * chk[0][i - 2] + stk[1][i]
        if tmp1 >= tmp2:
            chk[0][i] = 0
            if chk[1][i - 2] == 1:
                chk[1][i - 1] = 0
            dp[i] = dp[i - 2] + tmp1
        else:
            chk[1][i] = 0
            if chk[0][i - 2] == 1:
                chk[0][i - 1] = 0
            dp[i] = dp[i - 2] + tmp2
    
    print(dp[n])