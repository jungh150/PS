# 2️⃣ 플로이드-워셜 (Floyd-Warshall)

# 모든 정점에서 모든 정점까지의 최단 거리를 구하는 알고리즘 (O(N³))
# 음수 가중치 간선도 허용되지만, 음수 사이클이 있으면 적용 불가능하다.
INF = float('inf')

def floyd_warshall(graph, n):
    dist = [[INF] * n for _ in range(n)]

    for i in range(n):
        dist[i][i] = 0

    for u in range(n):
        for v, w in graph[u]:
            dist[u][v] = w

    for k in range(n):
        for i in range(n):
            for j in range(n):
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

    return dist