import sys
input = sys.stdin.readline

n, m, k = map(int, input().split())
map = [[1 for _ in range(m + 1)] for _ in range(n + 1)]

for i in range(2, n + 1):
    for j in range(2, m + 1):
        map[i][j] = map[i - 1][j] + map[i][j - 1]

if k == 0:
    print(map[n][m])
else:
    r = k // m + 1
    c = k % m
    print(map[r][c] * map[n - r + 1][m - c + 1])