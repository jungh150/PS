import sys
input = sys.stdin.readline

n, m, k = map(int, input().split())
dp = [[0 for _ in range(n + m + 1)] for _ in range(n + m + 1)]
ans = ''

dp[0][0] = 1

for i in range(1, n + m + 1):
    dp[i][0] = dp[i][i] = 1
    for j in range(1, i):
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]

if k > dp[n + m][n]:
    print(-1)
else:
    while n > 0 or m > 0:
        tmp = dp[n + m - 1][n - 1]
        if k < tmp: # 그 자리에 a 확정
            n -= 1
            ans += 'a'
        elif k > tmp: # 그 자리에 z 확정
            k -= tmp
            m -= 1
            ans += 'z'
        else: # k == tmp -> 그 자리에 a 확정 & 나머지 문자들도 확정
            n -= 1
            ans += ('a' + 'z' * m + 'a' * n)
            break
print(ans)