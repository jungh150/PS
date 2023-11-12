from sys import stdin
from collections import deque

n, m = map(int, stdin.readline().split())
maze = []
visited = [[False] * m for _ in range(n)]
count = 0
dir = [[1, 0], [-1, 0], [0, 1], [0, -1]]

for i in range(n):
    maze.append(list(map(int, stdin.readline().strip())))

que = deque()

que.append((0, 0))
visited[0][0] = True
while que:
    v = que.popleft()
    for k in range(4):
        x = v[0] + dir[k][0]
        y = v[1] + dir[k][1]
        if x >= 0 and y >= 0 and x < n and y < m:
            if maze[x][y] != 0 and not visited[x][y]:
                que.append((x, y))
                visited[x][y] = True
                maze[x][y] = maze[v[0]][v[1]] + 1

print(maze[n-1][m-1])