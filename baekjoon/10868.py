from sys import stdin
import math
import sys
sys.setrecursionlimit(10 ** 8)

n, m = map(int, stdin.readline().split())
treeHeight = math.ceil(math.log2(n)) + 1
treeSize = pow(2, treeHeight)
leafIndex = treeSize // 2
tree = [sys.maxsize] * (treeSize)

def getMin(a, b):
    s = leafIndex + a - 1
    e = leafIndex + b - 1
    res = sys.maxsize
    while s <= e:
        if s % 2 == 1:
            res = min(res, tree[s])
            s += 1
        if e % 2 == 0:
            res = min(res, tree[e])
            e -= 1
        s //= 2
        e //= 2
    return res

for i in range(leafIndex, leafIndex + n):
    tree[i] = int(stdin.readline())

# 트리 초기화
i = treeSize - 1
while i != 1:
    if tree[i] < tree[i // 2]:
        tree[i // 2] = tree[i]
    i -= 1

for _ in range(m):
    a, b = map(int, stdin.readline().split())
    print(getMin(a, b))