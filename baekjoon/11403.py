from sys import stdin

n = int(stdin.readline())
g = []

for _ in range(n):
    g.append(list(map(int, stdin.readline().split())))

for i in range(n): # 경유지 i에 관해
    for j in range(n): # 출발 노드 j 에 관해
        for k in range(n): # 도착 노드 k에 관해
            if g[j][i] == 1 and g[i][k] == 1:
                g[j][k] = 1

for i in range(n):
    for j in range(n):
        print(g[i][j], end=' ')
    print()