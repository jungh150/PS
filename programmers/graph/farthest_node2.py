from collections import deque

def solution(n, edge):
    adj = [[] for _ in range(n + 1)]
    for e in edge:
        adj[e[0]].append(e[1])
        adj[e[1]].append(e[0])

    vst = [-1 for _ in range(n + 1)]
    q = deque()
    
    vst[1] = 0
    q.append(1)
    while q:
        cur = q.popleft()
        for nxt in adj[cur]:
            if vst[nxt] == -1:
                vst[nxt] = vst[cur] + 1
                q.append(nxt)
    
    maxv = max(vst[1:])
    answer = vst.count(maxv)

    return answer