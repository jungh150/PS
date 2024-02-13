from sys import stdin

n = int(stdin.readline())
data = list(map(int, stdin.readline().split()))
delete = int(stdin.readline())
tree = [[] for _ in range(n)]
root = 0

def leaf(a):
    cnt = 0
    if len(tree[a]) == 0:
        return 1
    for nxt in tree[a]:
        cnt += leaf(nxt)
    return cnt

for i in range(n):
    if data[i] == -1:
        root = i
    else:
        if delete != i:
            tree[data[i]].append(i)

if root == delete:
    print(0)
else:
    print(leaf(root))