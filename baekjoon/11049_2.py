import sys
input = sys.stdin.readline

# top-down & memoization 방식

n = int(input())
m = []
# dp[i][j] : i번째 행렬부터 j번째 행렬까지 곱할 때 필요한 곱셈 연산의 수
dp = [[-1 for _ in range(n)] for _ in range(n)]

for _ in range(n):
    a, b = map(int, input().split())
    m.append([a, b])

def execute(s, e):
    if dp[s][e] != -1:
        return dp[s][e]
    if s == e:
        return 0
    if s + 1 == e:
        return m[s][0] * m[s][1] * m[e][1]
    res = sys.maxsize
    for i in range(s, e):
        res = min(res, m[s][0] * m[i][1] * m[e][1] + execute(s, i) + execute(i + 1, e))
    dp[s][e] = res
    return dp[s][e]

print(execute(0, n - 1))