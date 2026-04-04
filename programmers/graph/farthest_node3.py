import heapq

MAX_VAL = 1000000

def solution(n, edge):
    adj = [[] for _ in range(n + 1)]
    for e in edge:
        adj[e[0]].append((e[1], 1))
        adj[e[1]].append((e[0], 1))

    dst = [MAX_VAL for _ in range(n + 1)]
    q = []
    
    dst[1] = 0
    heapq.heappush(q, (0, 1))
    while q:
        val, cur = heapq.heappop(q)

        # 이게 필요한 이유:
        # 힙에는 같은 노드가 여러 번 들어갈 수 있어서, 이미 더 짧은 거리로 처리된 노드면 스킵하는 것이 좋음.
        if val > dst[cur]:
            continue
        
        for nxt, d in adj[cur]:
            if val + d < dst[nxt]:
                dst[nxt] = val + d
                heapq.heappush(q, (val + d, nxt))
    
    maxv = max(dst[1:])
    answer = dst.count(maxv)

    return answer