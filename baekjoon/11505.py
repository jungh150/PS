import sys
import math
input = sys.stdin.readline

div = 1000000007
n, m, k = map(int, input().split())
treeHeight = math.ceil(math.log2(n)) + 1
treeSize = pow(2, treeHeight)
leafIndex = treeSize // 2
tree = [1] * treeSize

def change(b, c):
    index = leafIndex + b - 1
    tree[index] = c
    if index % 2 == 0:
        nxt = index + 1
    else:
        nxt = index - 1
    while index != 1:
        tree[index // 2] = tree[index] * tree[nxt]
        tree[index // 2] %= div
        index //= 2
        if index % 2 == 0:
            nxt = index + 1
        else:
            nxt = index - 1

def getAns(b, c):
    s = leafIndex + b - 1
    e = leafIndex + c - 1
    res = 1
    while s <= e:
        if s % 2 == 1:
            res *= tree[s]
            res %= div
            s += 1
        if e % 2 == 0:
            res *= tree[e]
            res %= div
            e -= 1
        s //= 2
        e //= 2
    return res

for i in range(leafIndex, leafIndex + n):
    tree[i] = int(input())

i = treeSize - 1
while i != 1:
    tree[i // 2] *= tree[i]
    tree[i // 2] %= div
    i -= 1

for _ in range(m + k):
    a, b, c = map(int, input().split())
    if a == 1:
        change(b, c)
    elif a == 2:
        print(getAns(b, c))