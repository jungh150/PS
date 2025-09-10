import sys
input = sys.stdin.readline
sys.setrecursionlimit(10000000)

n = int(input())

adj = [[] for _ in range(n + 1)]
for _ in range(n - 1):
    a, b = map(int, input().split())
    adj[a].append(b)
    adj[b].append(a)

# dp[i][j]: i번 노드가 j 상태일 때, i번 노드를 루트로 하는 서브트리에서 필요한 early adaptor 최소 개수
dp = [[-1 for _ in range(2)] for _ in range(n + 1)]
vst = [False for _ in range(n + 1)]

def td(pre, cur, st):
    vst[cur] = True

    if dp[cur][st] != -1:
        return dp[cur][st]

    dp[cur][st] = st
    if st == 0: # not early adaptor
        for nxt in adj[cur]:
            if nxt == pre:
                continue
            dp[cur][st] += td(cur, nxt, 1)
    elif st == 1: # early adaptor
        for nxt in adj[cur]:
            if nxt == pre:
                continue
            dp[cur][st] += min(td(cur, nxt, 0), td(cur, nxt, 1))
    
    return dp[cur][st]

print(min(td(-1, 1, 0), td(-1, 1, 1)))