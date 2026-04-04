from collections import deque

def solution(n, edge):
    adj = [[] for _ in range(n + 1)]
    for e in edge:
        adj[e[0]].append(e[1])
        adj[e[1]].append(e[0])

    vst = [-1 for _ in range(n + 1)]
    q = deque()
    
    vst[1] = 0
    q.append((1, 0))
    while q:
        cur, cnt = q.popleft()
        for nxt in adj[cur]:
            if vst[nxt] == -1:
                vst[nxt] = cnt + 1
                q.append((nxt, cnt + 1))
    
    maxv = 0
    answer = 1
    for i in range(1, n + 1):
        if vst[i] == maxv:
            answer += 1
        elif vst[i] > maxv:
            maxv = vst[i]
            answer = 1

    return answer