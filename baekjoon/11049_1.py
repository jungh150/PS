import sys
input = sys.stdin.readline

# bottom-up 방식

n = int(input())
m = []
# dp[i][j] : i번째 행렬부터 j번째 행렬까지 곱할 때 필요한 곱셈 연산의 수
dp = [[0 for _ in range(n)] for _ in range(n)]

for _ in range(n):
    a, b = map(int, input().split())
    m.append([a, b])

for i in range(1, n):
    for j in range(n - i):
        dp[j][j + i] = sys.maxsize
        for k in range(j, j + i):
            dp[j][j + i] = min(dp[j][j + i], dp[j][k] + dp[k + 1][j + i] + m[j][0] * m[k][1] * m[j + i][1])

print(dp[0][n - 1])