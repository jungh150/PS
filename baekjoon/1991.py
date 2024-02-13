from sys import stdin

n = int(stdin.readline())
tree = {}

for _ in range(n):
    self, left, right = stdin.readline().split()
    tree[self] = [left, right]

def preOrder(now):
    if now != '.':
        print(now, end='')
        preOrder(tree[now][0])
        preOrder(tree[now][1])

def inOrder(now):
    if now != '.':
        inOrder(tree[now][0])
        print(now, end='')
        inOrder(tree[now][1])

def postOrder(now):
    if now != '.':
        postOrder(tree[now][0])
        postOrder(tree[now][1])
        print(now, end='')

preOrder('A')
print()
inOrder('A')
print()
postOrder('A')