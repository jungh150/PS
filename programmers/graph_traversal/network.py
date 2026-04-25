from collections import deque

def solution(n, computers):
    answer = 0

    adj = [[] for _ in range(n)]
    for i in range(n):
        for j in range(n):
            if i == j:
                continue
            if (computers[i][j] == 1):
                adj[i].append(j)
    
    vst = [False for _ in range(n)]
    q = deque()
    
    for i in range(n):
        if vst[i]:
            continue
        
        answer += 1
        vst[i] = True
        q.append(i)
        while q:
            cur = q.popleft()
            for nxt in adj[cur]:
                if not vst[nxt]:
                    vst[nxt] = True
                    q.append(nxt)
    
    return answer