from sys import stdin
import math

n, m, k = map(int, stdin.readline().split())
treeHeight = math.ceil(math.log2(n)) + 1
treeSize = pow(2, treeHeight)
leafIndex = treeSize // 2
tree = [0] * (treeSize)

def change(b, c):
    index = leafIndex + b - 1
    diff = c - tree[index]
    while index != 0:
        tree[index] += diff
        index //= 2

def sum(b, c):
    s = leafIndex + b - 1
    e = leafIndex + c - 1
    res = 0
    while s <= e:
        if s % 2 == 1:
            res += tree[s]
            s += 1
        if e % 2 == 0:
            res += tree[e]
            e -= 1
        s //= 2
        e //= 2
    return res

for i in range(leafIndex, leafIndex + n):
    tree[i] = int(stdin.readline())

# 트리 초기화
i = treeSize - 1
while i != 1:
    tree[i // 2] += tree[i]
    i -= 1

for _ in range(m + k):
    a, b, c = map(int, stdin.readline().split())
    if a == 1:
        change(b, c)
    elif a == 2:
        print(sum(b, c))