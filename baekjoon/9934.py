import sys
input = sys.stdin.readline

k = int(input())
visit = list(map(int, input().split()))
tree = {}

for i in range(1, pow(2, k-1)):
    tree[i] = [i*2, i*2 + 1, 0]

def inOrder(now, i):
    if now != '.':
        inOrder(tree[now][0], i)
        tree[now][3] = visit[i]
        print(tree[now][3])
        i += 1
        inOrder(tree[now][1], i)

inOrder(1, 0)