import sys
input = sys.stdin.readline

k = int(input())
visit = list(map(int, input().split()))
tree = {}

for i in range(1, pow(2, k-1)):
    tree[i] = [i*2, i*2 + 1, 0]

for i in range(pow(2, k-1), pow(2, k)):
    tree[i] = ['.', '.', 0]

def inOrder(now):
    global i
    if now != '.':
        inOrder(tree[now][0])
        tree[now][2] = visit[i]
        i += 1
        inOrder(tree[now][1])

i = 0
inOrder(1)

level = 1
for i in range(1, pow(2, k)):
    if i == pow(2, level):
        print()
        level += 1
    print(tree[i][2], end=' ')