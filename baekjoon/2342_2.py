import sys
input = sys.stdin.readline

p = [[0, 2, 2, 2, 2], # 0에서 다른 칸으로 움직일 때 드는 힘
     [2, 1, 3, 4, 3], # 1에서 다른 칸으로 움직일 때 드는 힘
     [2, 3, 1, 3, 4], # 2에서 다른 칸으로 움직일 때 드는 힘
     [2, 4, 3, 1, 3], # 3에서 다른 칸으로 움직일 때 드는 힘
     [2, 3, 4, 3, 1]] # 4에서 다른 칸으로 움직일 때 드는 힘

data = list(map(int, input().split()))
n = len(data) - 1

# dp[n][l][r] : n번째 지시 사항까지 완료한 후 왼발의 위치가 l이고 오른발의 위치가 r일 때 최소 누적 합
dp = [[[sys.maxsize for _ in range(5)] for _ in range(5)] for _ in range(n + 1)]
dp[0][0][0] = 0

for i in range(1, n + 1):
    for j in range(5):
        if j != data[i - 1]:
            for k in range(5):
                dp[i][data[i - 1]][j] = min(dp[i - 1][k][j] + p[k][data[i - 1]], dp[i][data[i - 1]][j])
    for j in range(5):
        if j != data[i - 1]:
            for k in range(5):
                dp[i][j][data[i - 1]] = min(dp[i - 1][j][k] + p[k][data[i - 1]], dp[i][j][data[i - 1]])

ans = sys.maxsize
for i in range(5):
    ans = min(ans, dp[n][i][data[n - 1]])
    ans = min(ans, dp[n][data[n - 1]][i])

print(ans)