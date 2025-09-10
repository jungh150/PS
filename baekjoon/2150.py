import sys
input = sys.stdin.readline
sys.setrecursionlimit(100000)

v, e = map(int, input().split())
adj1 = [[] for _ in range(v + 1)]
adj2 = [[] for _ in range(v + 1)]
stk = []

def dfs1(cur):
    vst[cur] = True
    for nxt in adj1[cur]:
        if not vst[nxt]:
            dfs1(nxt)
    stk.append(cur)

def dfs2(cur):
    tmp.append(cur)
    vst[cur] = True
    for nxt in adj2[cur]:
        if not vst[nxt]:
            dfs2(nxt)

for _ in range(e):
    a, b = map(int, input().split())
    adj1[a].append(b)
    adj2[b].append(a)

vst = [False for _ in range(v + 1)]
for i in range(1, v + 1):
    if (not vst[i]):
        dfs1(i)

ans = []
vst = [False for _ in range(v + 1)]
while stk:
    x = stk.pop()
    if not vst[x]:
        tmp = []
        dfs2(x)
        ans.append(tmp)

for i in range(len(ans)):
    ans[i].sort()
ans.sort()

print(len(ans))
for x in ans:
    for y in x:
        print(y, end = ' ')
    print(-1)