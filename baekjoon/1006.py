import sys
input = sys.stdin.readline

T = int(input())

def bu():
    for j in range(2, n + 1):
        # dp[0][j] 채우기
        dp[0][j] = dp[2][j - 1] + 1
        if a[0][j - 1] + a[0][j] <= w:
            dp[0][j] = min(dp[0][j], dp[1][j - 1] + 1)
        
        # dp[1][j] 채우기
        dp[1][j] = dp[2][j - 1] + 1
        if a[1][j - 1] + a[1][j] <= w:
            dp[1][j] = min(dp[1][j], dp[0][j - 1] + 1)

        # dp[2][j] 채우기
        dp[2][j] = dp[2][j - 1] + 2
        if a[0][j] + a[1][j] <= w:
            dp[2][j] = min(dp[2][j], dp[2][j - 1] + 1)
        if (a[0][j - 1] + a[0][j] <= w) and (a[1][j - 1] + a[1][j] <= w):
            dp[2][j] = min(dp[2][j], dp[2][j - 2] + 2)
        if a[0][j - 1] + a[0][j] <= w:
            dp[2][j] = min(dp[2][j], dp[1][j - 1] + 2)
        elif a[1][j - 1] + a[1][j] <= w:
            dp[2][j] = min(dp[2][j], dp[0][j - 1] + 2)

for _ in range(T):
    n, w = map(int, input().split())
    a = []
    for _ in range(2):
        a.append([0] + list(map(int, input().split())))
    
    if n == 1:
        if a[0][1] + a[1][1] <= w:
            print(1)
        else:
            print(2)
        continue
    
    # dp[0][j]: 0행은 j까지, 1행은 j-1까지 봤을 때 필요한 특수 소대의 최소 개수
    # dp[1][j]: 0행은 j-1까지, 1행은 j까지 봤을 때 필요한 특수 소대의 최소 개수
    # dp[2][j]: 0행, 1행 모두 j까지 봤을 때 필요한 특수 소대의 최소 개수
    dp = [[0 for _ in range(n + 1)] for _ in range(3)]

    # 병합 X
    dp[0][1] = 1
    dp[1][1] = 1
    if a[0][1] + a[1][1] <= w:
        dp[2][1] = 1
    else:
        dp[2][1] = 2
    bu()
    ans = dp[2][n]
    
    tmp0 = a[0][1]
    tmp1 = a[1][1]
    tmp2 = a[0][n]
    tmp3 = a[1][n]

    # a[0][1], a[0][n] 병합
    if a[0][1] + a[0][n] <= w:
        a[0][1] = w + 1
        a[0][n] = w + 1
        dp[0][1] = 0
        dp[1][1] = 1
        dp[2][1] = 1
        bu()
        ans = min(ans, dp[2][n])
        a[0][1] = tmp0 # 복구
        a[0][n] = tmp2 # 복구

    # a[1][1], a[1][n] 병합
    if a[1][1] + a[1][n] <= w:
        a[1][1] = w + 1
        a[1][n] = w + 1
        dp[0][1] = 1
        dp[1][1] = 0
        dp[2][1] = 1
        bu()
        ans = min(ans, dp[2][n])
        a[1][1] = tmp1 # 복구
        a[1][n] = tmp3 # 복구

    # a[0][1], a[0][n] 병합 & a[1][1], a[1][n] 병합
    if (a[0][1] + a[0][n] <= w) and (a[1][1] + a[1][n] <= w):
        a[0][1] = w + 1
        a[1][1] = w + 1
        dp[0][1] = 0
        dp[1][1] = 0
        dp[2][1] = 0
        bu()
        ans = min(ans, dp[2][n - 1] + 2)
    
    print(ans)